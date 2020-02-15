#include "MidiBLEDevice.h"
#include "IMidiLightedButton.h"

#pragma once
#ifndef DMIDICCBUTTON_H
#define DMIDICCBUTTON_H

// If you want note on/off buttons to latch or not...
#define BUTTON_PRESS_TYPE_MOMENTARY   1
#define BUTTON_PRESS_TYPE_LATCHING    2

// Defines what is needed to make each button unit work...
class MidiCCButton : public IMidiLightedButton {

  public:
    int id;
    int button_pin;
    int led_pin;
    int midi_channel;
    int midi_note;
    // For our current midi button press state
    bool is_on;
    MidiBLEDevice *midiBleDevice;

    MidiCCButton( MidiBLEDevice *cMidiBleDevice, int cid, int cbutton_pin, int cled_pin, int cmidi_channel, int cmidi_note );
    void initGPIOPins();
    void resetState();
    void handleState();
    void turnLEDOff();
    void turnLEDOn();
  private:
    // To track momentary button press HIGH/LOW
    int last_button_state;

};

#endif
