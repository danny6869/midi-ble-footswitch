#include <Arduino.h>
#include "config.h"
#include "LEDAnimation.h"
#include "MidiController.h"
#include "MidiButton.h"
#include "MidiExpressionPedal.h"

MidiController::MidiController( const char *cDeviceName )
{
  deviceName = cDeviceName;

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

  if ( !midiBleDevice->hasSubscriberConnected() ) {
    // No bluetooth midi subscriber yet...
    Serial.println("Waiting for MIDI BLE subscriber via BLE");
    // Do connection animation while we wait...
    show_current_bluetooth_animation_frame(buttonList, buttonCount);
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

}

void MidiController::start()
{

  // Initialize our microcontroller pins...
  _init_input_pins();

  // Show the bootup sequence...
  show_bootup_animation_sequence(this->buttonList, this->buttonCount);

}

void MidiController::_init_input_pins()
{

  // Setup our button unit pins...
  for ( int i = 0; i < buttonCount; i++) {
    pinMode(buttonList[i]->button_pin, INPUT_PULLUP);
    pinMode(buttonList[i]->led_pin, OUTPUT);
  }

  // Setup our button unit pins...
  for ( int i = 0; i < expressionPedalCount; i++) {
    pinMode(expressionPedalList[i]->button_pin, INPUT);
  }

}
