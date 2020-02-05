#include <stdio.h>
#include "config.h"
#include "LEDAnimation.h"
#include "MidiButton.h"

// Somewhere to keep what frame we are currently displaying...
int _bluetooth_connection_animation_frame = 1;

void _light_buttons_on_off(MidiButton **buttonList, int buttonCount, int numTimes) {

  /*
     Lights all buttons ON, then then OFF.
  */

  for (int x = 0; x < numTimes; x++) {

    // All on...
    for (int i = 0; i < buttonCount; i++) {
      digitalWrite(buttonList[i]->led_pin, LED_ON);
    }

    delay(BOOTUP_ANIMATION_DELAY);

    // All off...
    for (int i = 0; i < buttonCount; i++) {
      digitalWrite(buttonList[i]->led_pin, LED_OFF);
    }

    delay(BOOTUP_ANIMATION_DELAY);
  }

}

void _light_buttons_left_to_right(MidiButton **buttonList, int buttonCount) {
  /*
     Lights buttons from left to right one by one.
  */

  for ( int i = 0; i < buttonCount; i++ ) {
    digitalWrite(buttonList[i]->led_pin, LED_ON);
    delay(BOOTUP_ANIMATION_DELAY);
    digitalWrite(buttonList[i]->led_pin, LED_OFF);
  }

  delay(BOOTUP_ANIMATION_DELAY);

}

void _light_buttons_left_to_right_to_left(MidiButton **buttonList, int buttonCount) {

  /*
     Lights buttons from left to right, and then right to left one by one.
  */

  for ( int i = 0; i < buttonCount; i++ ) {
    digitalWrite(buttonList[i]->led_pin, LED_ON);
    delay(BOOTUP_ANIMATION_DELAY);
    digitalWrite(buttonList[i]->led_pin, LED_OFF);
  }

  // Skip the extra one on the end, as we don't
  // want it to light up twice from the loop above...
  for ( int i = buttonCount - 2; i >= 0; i-- ) {
    digitalWrite(buttonList[i]->led_pin, LED_ON);
    delay(BOOTUP_ANIMATION_DELAY);
    digitalWrite(buttonList[i]->led_pin, LED_OFF);
  }

  delay(BOOTUP_ANIMATION_DELAY);

}

void show_bootup_animation_complete(MidiButton **buttonList, int buttonCount) {
  /*
     This is called after the initial boot sequence/animation.
  */
  _light_buttons_on_off(buttonList, buttonCount, 2);
}


void show_bootup_animation_sequence(MidiButton **buttonList, int buttonCount) {
  /*
     This is called when the unit is first powered on.  It's job is to light all button LEDs
     to allow for a visual check that they are all working.
  */
  Serial.println("Starting self-test/bootup animation");
  _light_buttons_left_to_right_to_left(buttonList, buttonCount);
  show_bootup_animation_complete(buttonList, buttonCount);
}

void show_current_bluetooth_animation_frame(MidiButton **buttonList, int buttonCount) {
  /*
     This is called within the main program loop() whenever we area awaiting a
     bluetooth connection, with a MIDI BLE characteristic subscriber.

     Draws the current animation frame for the bluetooth connecting animation.  This
     animation just lights every other button LED alnternately with each frame So,
     essentially (assuming 4 buttons/leds)...

       1 0 1 0
       0 1 0 1
       1 0 1 0
       ...etc...
  */

  // How many frames we want to show...
  static int _NUM_FRAMES = 2;

  for ( int i = 0; i < buttonCount; i++ ) {
    if ( ( i % _NUM_FRAMES ) + 1 == _bluetooth_connection_animation_frame ) {
      digitalWrite(buttonList[i]->led_pin, LED_ON);
    } else {
      digitalWrite(buttonList[i]->led_pin, LED_OFF);
    }
  }

  if ( _bluetooth_connection_animation_frame >= _NUM_FRAMES ) {
    _bluetooth_connection_animation_frame = 1;

  } else {
    _bluetooth_connection_animation_frame++;
  }

  // Do our animation pause here to keep it all self contained...
  delay(BLUETOOTH_AWAITING_CONNECTION_ANIMATION_DELAY);
}

void restart_bluetooth_animation_sequence(MidiButton **buttonList, int buttonCount) {
  /* This is called within the main program loop() whenever we have dropped an active
     bluetooth connection, with a MIDI BLE characteristic subscriber...so we can
     re-start our bluetooth connection animation.  Also draws the first frame.
  */
  _bluetooth_connection_animation_frame = 1;
  show_current_bluetooth_animation_frame(buttonList, buttonCount);
}
