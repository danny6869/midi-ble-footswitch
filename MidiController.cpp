#include <Arduino.h>
#include "config.h"
#include "LEDAnimation.h"
#include "MidiController.h"
#include "MidiButton.h"
#include "MidiExpressionPedal.h"

MidiController::MidiController( const char *cDeviceName )
{
  deviceName = cDeviceName;
  last_pass_had_subscriber_connected = false;

  // Setup our MIDI BLE device...
  midiBleDevice = new MidiBLEDevice( (char *) deviceName );

}

void MidiController::addButton( int buttonPinNumber, int ledPinNumber, int midiChannelNumber, int midiNoteNumber, int buttonType )
{
  // Double-check to make sure we're not exceeding our bounds...
  if ( buttonCount >= _MAX_MIDI_CONTROLLER_BUTTONS ) {
    Serial.println("ERROR: MAXIMUM NUMBER OF BUTTONS REACHED!!!");
    return;
  }

  // Create the new button...
  int buttonId = _get_next_id();
  MidiButton *buttonObj = new MidiButton( midiBleDevice, buttonId, buttonPinNumber, ledPinNumber, midiChannelNumber, midiNoteNumber, buttonType );

  // Add it to our list (incrementing our counter too)...
  buttonList[buttonCount] = buttonObj;
  buttonCount++;
}

void MidiController::addExpressionPedal( int expressionPedalPinNumber, int midiChannelNumber, int pedalDirection, int curveType )
{
  // Double-check to make sure we're not exceeding our bounds...
  if ( expressionPedalCount >= _MAX_MIDI_CONTROLLER_EXPRESSION_PEDALS ) {
    Serial.println("ERROR: MAXIMUM NUMBER OF EXPRESSION PEDALS REACHED!!!");
    return;
  }

  // Create the new expressionPedal...
  int expressionPedalId = _get_next_id();
  MidiExpressionPedal *expressionPedalObj = new MidiExpressionPedal( midiBleDevice, expressionPedalId, expressionPedalPinNumber, midiChannelNumber, pedalDirection, curveType);

  // Add it to our list (incrementing our counter too)...
  expressionPedalList[expressionPedalCount] = expressionPedalObj;
  expressionPedalCount++;
}

int MidiController::_get_next_id()
{
  static int id = 1;
  return id++;
}

void MidiController::loop()
{
  // Our main loop for the controller...handle all controls from here...

  // Call the MIDI-BLE device's loop() so it can detect, and track the bluetooth related stuff...
  midiBleDevice->loop();

  bool has_subscriber_connected = midiBleDevice->hasSubscriberConnected();

  if ( !has_subscriber_connected ) {
    // No bluetooth midi subscriber...

    if ( last_pass_had_subscriber_connected ) {
      // We just lost our subscriber...
      Serial.println("Lost MIDI BLE subscriber");
      // Restart the connection animation...
      restart_bluetooth_animation_sequence(buttonList, buttonCount);
    } else {
      // Waiting for a subscriber...
      Serial.println("Waiting for MIDI BLE subscriber");
      // Do connection animation while we wait...
      show_current_bluetooth_animation_frame(buttonList, buttonCount);
    }

  } else if ( !last_pass_had_subscriber_connected ) {
    // A MIDI BLE subscriber has just connected...
    Serial.println("New MIDI BLE subscriber");
    // Reset our button states (incase this was from a previous BLE disconnect)...
    Serial.println("Initializing button states");
    for ( int i = 0; i < buttonCount; i++) {
      buttonList[i]->reset_button_state();
    }
  } else {
    // We have a MIDI BLE subscriber...

    // Handle any button presses...
    for ( int i = 0; i < buttonCount; i++ ) {
      buttonList[i]->handleState();
    }

    // Handle any expression pedal movement...
    for ( int i = 0; i < expressionPedalCount; i++ ) {
      expressionPedalList[i]->handleState();
    }

    delay(DELAY_TIME_BETWEEN_INPUT_SCANS);
  }

  // Keep track of the connection state so we know WHEN it changes for proper resetting...
  last_pass_had_subscriber_connected = has_subscriber_connected;

}

void MidiController::start() {

  // Initialize our microcontroller pins...
  _init_input_pins();

  // Show the bootup sequence...
  show_bootup_animation_sequence(this->buttonList, this->buttonCount);

}

void MidiController::_init_input_pins() {

  // Setup all of the I/O pins for each component

  // Buttons...
  for ( int i = 0; i < buttonCount; i++) {
    buttonList[i]->init_gpio_pins();
  }

  // Expression pedals...
  for ( int i = 0; i < expressionPedalCount; i++) {
    buttonList[i]->init_gpio_pins();
  }

}
