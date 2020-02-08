#include "MidiButton.h"
#include "config.h"

MidiButton::MidiButton( MidiBLEDevice *cMidiBleDevice, int cid, int cbutton_pin, int cled_pin, int cmidi_channel, int cmidi_note, int cbutton_type ) {
  id                = cid;
  midiBleDevice     = cMidiBleDevice;
  button_pin        = cbutton_pin;
  led_pin           = cled_pin;
  midi_channel      = cmidi_channel;
  midi_note         = cmidi_note;
  button_type       = cbutton_type;
  is_on             = false;
  last_button_state = BUTTON_NOT_PRESSED;
}

void MidiButton::handleState() {

  // Default to our current value...
  int new_is_on = is_on;

  // Read in the current button state...
  int temp_button_state = digitalRead(button_pin);

  switch (button_type) {
    case BUTTON_PRESS_TYPE_MOMENTARY:
      if ( temp_button_state == BUTTON_PRESSED ) {
        new_is_on = true;
      } else {
        new_is_on = false;
      }
      break;
    case BUTTON_PRESS_TYPE_LATCHING:
      if ( ( temp_button_state == BUTTON_PRESSED ) and ( temp_button_state != last_button_state ) ) {
        // Button has been pressed, when it previously was not on the last pass...so we need to toggle...
        if ( is_on ) {
          // Currently on...toggle off...
          new_is_on = false;
        } else {
          // Currently off...toggle on...
          new_is_on = true;
        }
      } // else no change in state, nothing to update
      break;
    default:
      Serial.print("ERROR: Unknown value for button type: ");
      Serial.print(button_type);
      Serial.println();
      break;
  }

  if ( new_is_on != is_on ) {
    // New button press state...handle it...

    if ( new_is_on == true ) {
      digitalWrite(led_pin, LED_ON);
      midiBleDevice->sendMIDINoteOn( midi_channel, midi_note );
    } else {
      digitalWrite(led_pin, LED_OFF);
      midiBleDevice->sendMIDINoteOff( midi_channel, midi_note );
    }

    // Store the new on/off state to match what we just did...
    is_on = new_is_on;
  }

  // Update our last known status so we can detect when it changes
  // (separate from whether the button is currently on or off)...
  last_button_state = temp_button_state;

}

void MidiButton::reset_button_state() {
  /*
    This is called whenever a button needs to be reset back to its initial state.  It is called when a new BLE subscriber connects (or re-connects).
  */
  is_on = false;
  last_button_state = BUTTON_NOT_PRESSED;
  digitalWrite(led_pin, LED_OFF);
}

void MidiButton::init_gpio_pins() {
  /*
    Setup our button, and LED pins
  */
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);
  // Turn off the LED immediately
  digitalWrite(led_pin, LED_OFF);
}
