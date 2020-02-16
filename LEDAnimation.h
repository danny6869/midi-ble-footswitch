#pragma once
#include "IMidiLightedButton.h"

#ifndef DLEDANIMATION_H
#define DLEDANIMATION_H

void show_bootup_animation_sequence(IMidiLightedButton **buttonList, int buttonCount);
void restart_bluetooth_animation_sequence(IMidiLightedButton **buttonList, int buttonCount);
void show_current_bluetooth_animation_frame(IMidiLightedButton **buttonList, int buttonCount);

#endif
