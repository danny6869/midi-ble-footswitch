#pragma once
#include "MidiBLEProtocol.h"
#include "MidiBLEDevice.h"
#include "MidiButton.h"
#include "MidiExpressionPedal.h"

#ifndef DMIDICONTROLLER_H
#define DMIDICONTROLLER_H

#define _MAX_MIDI_CONTROLLER_BUTTONS             10
#define _MAX_MIDI_CONTROLLER_EXPRESSION_PEDALS   5

class MidiController {
  private:
    const char *deviceName;
    MidiBLEDevice *midiBleDevice;
    bool last_pass_had_subscriber_connected;

    // Non-dynamic list(s) to prevent allocation fragmentation
    MidiButton *buttonList[_MAX_MIDI_CONTROLLER_BUTTONS] = {};
    int buttonCount = 0;
    MidiExpressionPedal *expressionPedalList[_MAX_MIDI_CONTROLLER_EXPRESSION_PEDALS] = {};
    int expressionPedalCount = 0;

    int _get_next_id();
    void _init_input_pins();
  public:

    MidiController( const char *deviceName );
    void addButton( int buttonPinNumber, int ledPinNumber, int midiChannelNumber, int midiNoteNumber, int buttonType );
    void addExpressionPedal( int expressionPedalPinNumber, int midiChannelNumber, int pedalDirection, int curveType );
    void start();
    void loop();
};

#endif
