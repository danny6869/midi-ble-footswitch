#include "MidiBLEDevice.h"

#pragma once
#ifndef DMIDIBUTTON_H
#define DMIDIBUTTON_H

// If you want note on/off buttons to latch or not...
#define BUTTON_PRESS_TYPE_MOMENTARY   1
#define BUTTON_PRESS_TYPE_LATCHING    2

// Defines what is needed to make each button unit work...
class MidiButton {

  public:
    int id;
    int button_pin;
    int led_pin;
    int midi_channel;
    int midi_note;
    int button_type;
    // For our current midi button press state
    bool is_on;
    MidiBLEDevice *midiBleDevice;

    MidiButton( MidiBLEDevice *cMidiBleDevice, int cid, int cbutton_pin, int cled_pin, int cmidi_channel, int cmidi_note, int cbutton_type );
    void init_gpio_pins();
    void reset_button_state();
    void handleState();
  private:
    // To track momentary button press HIGH/LOW
    int last_button_state;

};

#endif
