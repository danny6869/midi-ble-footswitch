#include "MidiBLEDevice.h"
#include "IMidiLightedButton.h"

#pragma once
#ifndef DMIDICCBUTTON_H
#define DMIDICCBUTTON_H

// Defines what is needed to make each button unit work...
class MidiCCButton : public IMidiLightedButton {

  public:
    int id;
    int button_pin;
    int led_pin;
    int midi_channel;
    int midi_control_number;
    // For our current midi button press state
    bool is_on;
    MidiBLEDevice *midiBleDevice;

    MidiCCButton( MidiBLEDevice *cMidiBleDevice, int cid, int cbutton_pin, int cled_pin, int cmidi_channel, int cmidi_control_number );
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
