#include <bluefruit.h>
#include <MIDI.h>

#ifndef DMIDIBLEDEVICE_H
#define DMIDIBLEDEVICE_H

class MidiBLEDevice {

  private:

    // Setup our bluetooth device according to the MIDI BLE spec...

  public:

    char *deviceName;

    MidiBLEDevice( char *cDeviceName );
    void startBLEAdvertising();
    void loop();

    bool hasSubscriberConnected();

    void sendMIDINoteOff( int midi_channel, int midi_note );
    void sendMIDINoteOn( int midi_channel, int midi_note );
    void sendMIDIControlChange( int midi_channel, int midi_control_number, int midi_control_position );

};

#endif
