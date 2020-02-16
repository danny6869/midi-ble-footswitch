#include "MidiCCButton.h"
#include "config.h"

MidiCCButton::MidiCCButton( MidiBLEDevice *cMidiBleDevice, int cid, int cbutton_pin, int cled_pin, int cmidi_channel, int cmidi_control_number ) {
  id                  = cid;
  midiBleDevice       = cMidiBleDevice;
  button_pin          = cbutton_pin;
  led_pin             = cled_pin;
  midi_channel        = cmidi_channel;
  midi_control_number = cmidi_control_number;
  is_on               = false;
  last_button_state   = BUTTON_NOT_PRESSED;
}

void MidiCCButton::handleState() {

  // Default to our current value...
  int new_is_on = is_on;

  // Read in the current button state...
  int temp_button_state = digitalRead(button_pin);

  if ( temp_button_state == BUTTON_PRESSED ) {
    new_is_on = true;
  } else {
    new_is_on = false;
  }

  if ( new_is_on != is_on ) {
    // New button press state...handle it...

    if ( new_is_on == true ) {
      turnLEDOn();
      midiBleDevice->sendMIDIControlChange( midi_channel, midi_control_number, 127 );
    } else {
      turnLEDOff();
      midiBleDevice->sendMIDIControlChange( midi_channel, midi_control_number, 0 );
    }

    // Store the new on/off state to match what we just did...
    is_on = new_is_on;
  }

  // Update our last known status so we can detect when it changes
  // (separate from whether the button is currently on or off)...
  last_button_state = temp_button_state;

}

void MidiCCButton::resetState() {
  /*
    This is called whenever a button needs to be reset back to its initial state.  It is called when a new BLE subscriber connects (or re-connects).
  */
  is_on = false;
  last_button_state = BUTTON_NOT_PRESSED;
  turnLEDOff();
}

void MidiCCButton::initGPIOPins() {
  /*
    Setup our button, and LED pins
  */
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);
  // Turn off the LED immediately
  turnLEDOff();
}

void MidiCCButton::turnLEDOff() {
  digitalWrite(led_pin, LED_OFF);
}

void MidiCCButton::turnLEDOn() {
  digitalWrite(led_pin, LED_ON);
}
