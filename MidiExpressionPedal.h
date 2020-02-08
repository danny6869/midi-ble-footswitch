#include "MidiBLEDevice.h"

#pragma once

#ifndef DMIDIEXPRESSIONPEDAL_H
#define DMIDIEXPRESSIONPEDAL_H

// The response of the expression pedal
#define EXPRESSION_PEDAL_CURVE_LINEAR        1
#define EXPRESSION_PEDAL_CURVE_ACCELERATED   2
#define EXPRESSION_PEDAL_CURVE_DECELERATED   3

// The direction of the expression pedal
#define EXPRESSION_PEDAL_DIRECTION_LOW_TO_HIGH      1
#define EXPRESSION_PEDAL_DIRECTION_HIGH_TO_LOW      2

// Defines what is needed to make each button unit work...
class MidiExpressionPedal {
  public:
    int id;
    int button_pin;
    int midi_channel;
    int curve_type;
    int pedal_direction;
    MidiBLEDevice *midiBleDevice;

    MidiExpressionPedal( MidiBLEDevice *cMidiBleDevice, int cid, int cbutton_pin, int cmidi_channel, int cpedal_direction, int ccurve_type );
    void init_gpio_pins();
    void handleState();
  private:
    // To track our CC pedal value so we know when it changes...
    int last_midi_value;
};

#endif
