#include <stdio.h>
#include <Arduino.h>
#include "MidiBLEProtocol.h"

void MidiBLEProtocol::logMidiPacket(MidiBlePacket *packet) {

  Serial.print("PACKET: ");
  byte b;
  for (int i = 0; i < packet->size; i++) {
    Serial.print((int)packet->data[i]);
    // Separate with colons until the last one...
    if ( i != packet->size - 1 ) {
      Serial.print(":");
    }
  };
  Serial.println();

}

byte *MidiBLEProtocol::generateHeaderBytes() {
  /*
     This function takes care of the craziness of generating the header/timestamp bytes
     for a MIDI BLE packet according to the MIDI BLE spec.
  */

  // The timer is made up of 13 bits maximum according to the Midi BLE spec...
  int maxTimerBitsHigh = 6;
  int maxTimerBitsLow = 7;
  int maxTimerBits = maxTimerBitsHigh + maxTimerBitsLow;
  unsigned long timerBits = millis() % (int)pow( 2, maxTimerBits );
  byte highTimerBits = timerBits >> maxTimerBitsLow;
  byte lowTimerBits = timerBits & ((int)pow(2, maxTimerBitsLow) - 1 );

  // Header byte...
  // MIDI BLE Spec: 7th bit always 1, and the 6th bit always 0
  //                and the 6 high bits of the timestamp
  byte headerByte = 128 | highTimerBits;

  // Timestamp byte...
  // MIDI BLE Spec: 7th bit always 1
  //                and the 7 low bits of the timestamp
  byte timestampByte = 128 | lowTimerBits;

  byte *midiPacketHeaderBytes = new byte[2];
  midiPacketHeaderBytes[0] = headerByte;
  midiPacketHeaderBytes[1] = timestampByte;

  return midiPacketHeaderBytes;
}

MidiBlePacket *MidiBLEProtocol::generateNoteOnOffPacket(int channelNumber, int noteNumber, bool onOff) {
  /*
     Generates and returns a NOTE ON/OFF packet in full, ready for transmission.

          channelNumber: 1-16
          noteNUmber: 0-127
          onOff: 0-127
  */

  // Generate our header/timestamp bytes for this MIDI BLE packet...
  byte *bleHeaderBytes = generateHeaderBytes();
  byte headerByte = bleHeaderBytes[0];
  byte timestampByte = bleHeaderBytes[1];

  // MIDI Message bytes for NOTE ON/OFF...
  // 5th bit in the status byte signifies on/off
  byte statusByte = ( 128 + ( channelNumber - 1 ) ) | ( onOff ? 0b10000 : 0b00000 );

  // Note number...
  byte dataByte1 = noteNumber;

  // Velocity can always be 127 for on/off...
  byte dataByte2 = 127;

  struct MidiBlePacket *midiPacket = new MidiBlePacket();
  midiPacket->data = new byte[5] { headerByte, timestampByte, statusByte, dataByte1, dataByte2 };
  midiPacket->size = 5;

  return midiPacket;
}

MidiBlePacket *MidiBLEProtocol::generateControlChangePacket(int channelNumber, int pedalPosition) {
  /*
     Generates and returns a CONTROL CHANGE packet in full, ready for transmission.

          channelNumber: 1-16
          pedalPosition: 0-127
  */

  // Generate our header/timestamp bytes for this MIDI BLE packet...
  byte *bleHeaderBytes = generateHeaderBytes();
  byte headerByte = bleHeaderBytes[0];
  byte timestampByte = bleHeaderBytes[1];

  // MIDI Message bytes for control change...
  // Binary: 1011xxxx signifies control change...
  byte statusByte = ( 176 + (channelNumber - 1) );

  // Expression pedal (according to the MIDI spec)...
  byte controlNumber = 11;

  struct MidiBlePacket *midiPacket = new MidiBlePacket();
  midiPacket->data = new byte[5] { headerByte, timestampByte, statusByte, controlNumber, pedalPosition };
  midiPacket->size = 5;

  return midiPacket;
}
