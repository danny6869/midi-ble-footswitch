#pragma once

#include <BLEPeripheral.h>
#include <Arduino.h>

#ifndef DMIDIBLEUTIL_H
#define DMIDIBLEUTIL_H

#define MIDI_CHANNEL_1  1
#define MIDI_CHANNEL_2  2
#define MIDI_CHANNEL_3  3
#define MIDI_CHANNEL_4  4
#define MIDI_CHANNEL_5  5
#define MIDI_CHANNEL_6  6
#define MIDI_CHANNEL_7  7
#define MIDI_CHANNEL_8  8
#define MIDI_CHANNEL_9  9
#define MIDI_CHANNEL_10 10
#define MIDI_CHANNEL_11 11
#define MIDI_CHANNEL_12 12
#define MIDI_CHANNEL_13 13
#define MIDI_CHANNEL_14 14
#define MIDI_CHANNEL_15 15
#define MIDI_CHANNEL_16 16

#define MIDI_NOTE_A0    21
#define MIDI_NOTE_Bb0   22
#define MIDI_NOTE_B0    23
#define MIDI_NOTE_C1    24
#define MIDI_NOTE_Db1   25
#define MIDI_NOTE_D1    26
#define MIDI_NOTE_Eb1   27
#define MIDI_NOTE_E1    28
#define MIDI_NOTE_F1    29
#define MIDI_NOTE_Gb1   30
#define MIDI_NOTE_G1    31
#define MIDI_NOTE_Ab1   32
#define MIDI_NOTE_A1    33
#define MIDI_NOTE_Bb1   34
#define MIDI_NOTE_B1    35
#define MIDI_NOTE_C2    36
#define MIDI_NOTE_Db2   37
#define MIDI_NOTE_D2    38
#define MIDI_NOTE_Eb2   39
#define MIDI_NOTE_E2    40
#define MIDI_NOTE_F2    41
#define MIDI_NOTE_Gb2   42
#define MIDI_NOTE_G2    43
#define MIDI_NOTE_Ab2   44
#define MIDI_NOTE_A2    45
#define MIDI_NOTE_Bb2   46
#define MIDI_NOTE_B2    47
#define MIDI_NOTE_C3    48
#define MIDI_NOTE_Db3   49
#define MIDI_NOTE_D3    50
#define MIDI_NOTE_Eb3   51
#define MIDI_NOTE_E3    52
#define MIDI_NOTE_F3    53
#define MIDI_NOTE_Gb3   54
#define MIDI_NOTE_G3    55
#define MIDI_NOTE_Ab3   56
#define MIDI_NOTE_A3    57
#define MIDI_NOTE_Bb3   58
#define MIDI_NOTE_B3    59
#define MIDI_NOTE_C4    60
#define MIDI_NOTE_Db4   61
#define MIDI_NOTE_D4    62
#define MIDI_NOTE_Eb4   63
#define MIDI_NOTE_E4    64
#define MIDI_NOTE_F4    65
#define MIDI_NOTE_Gb4   66
#define MIDI_NOTE_G4    67
#define MIDI_NOTE_Ab4   68
#define MIDI_NOTE_A4    69
#define MIDI_NOTE_Bb4   70
#define MIDI_NOTE_B4    71
#define MIDI_NOTE_C5    72
#define MIDI_NOTE_Db5   73
#define MIDI_NOTE_D5    74
#define MIDI_NOTE_Eb5   75
#define MIDI_NOTE_E5    76
#define MIDI_NOTE_F5    77
#define MIDI_NOTE_Gb5   78
#define MIDI_NOTE_G5    79
#define MIDI_NOTE_Ab5   80
#define MIDI_NOTE_A5    81
#define MIDI_NOTE_Bb5   82
#define MIDI_NOTE_B5    83
#define MIDI_NOTE_C6    84
#define MIDI_NOTE_Db6   85
#define MIDI_NOTE_D6    86
#define MIDI_NOTE_Eb6   87
#define MIDI_NOTE_E6    88
#define MIDI_NOTE_F6    89
#define MIDI_NOTE_Gb6   90
#define MIDI_NOTE_G6    91
#define MIDI_NOTE_Ab6   92
#define MIDI_NOTE_A6    93
#define MIDI_NOTE_Bb6   94
#define MIDI_NOTE_B6    95
#define MIDI_NOTE_C7    96
#define MIDI_NOTE_Db7   97
#define MIDI_NOTE_D7    98
#define MIDI_NOTE_Eb7   99
#define MIDI_NOTE_E7    100
#define MIDI_NOTE_F7    101
#define MIDI_NOTE_Gb7   102
#define MIDI_NOTE_G7    103
#define MIDI_NOTE_Ab7   104
#define MIDI_NOTE_A7    105
#define MIDI_NOTE_Bb7   106
#define MIDI_NOTE_B7    107
#define MIDI_NOTE_C8    108
#define MIDI_NOTE_Db8   109
#define MIDI_NOTE_D8    110
#define MIDI_NOTE_Eb8   111
#define MIDI_NOTE_E8    112
#define MIDI_NOTE_F8    113
#define MIDI_NOTE_Gb8   114
#define MIDI_NOTE_G8    115
#define MIDI_NOTE_Ab8   116
#define MIDI_NOTE_A8    117
#define MIDI_NOTE_Bb8   118
#define MIDI_NOTE_B8    119
#define MIDI_NOTE_C9    120
#define MIDI_NOTE_Db9   121
#define MIDI_NOTE_D9    122
#define MIDI_NOTE_Eb9   123
#define MIDI_NOTE_E9    124
#define MIDI_NOTE_F9    125
#define MIDI_NOTE_Gb9   126
#define MIDI_NOTE_G9    127

struct MidiBlePacket {
  byte *data;
  int size;
};

class MidiBLEProtocol {
  private:
    static byte *generateHeaderBytes();
  public:
    static MidiBlePacket *generateNoteOnOffPacket(int channelNumber, int noteNumber, bool onOff);
    static MidiBlePacket *generateControlChangePacket(int channelNumber, int pedalPosition);
    static void logMidiPacket(MidiBlePacket * packet);
};

#endif
