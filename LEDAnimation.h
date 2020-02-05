#pragma once
#include "MidiButton.h"

#ifndef DLEDANIMATION_H
#define DLEDANIMATION_H

void show_bootup_animation_sequence(MidiButton **buttonList, int buttonCount);
void restart_bluetooth_animation_sequence(MidiButton **buttonList, int buttonCount);
void show_current_bluetooth_animation_frame(MidiButton **buttonList, int buttonCount);

#endif
