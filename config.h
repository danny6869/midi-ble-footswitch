#pragma once
#include <Arduino.h>

#ifndef DCONFIG_H
#define DCONFIG_H

/*
   Configurations
*/

// Device name as seen in your bluetooth devices...
// TODO: Document max chars --- 20 I think!?
#define BLE_DEVICE_NAME					"Midi BLE Pedal 3D"

// Some micro-controllers have these reversed (much to my surprise), so the
// code will honour this for LED on/off commands...
#define LED_ON						HIGH
#define LED_OFF						LOW

// For much the same reason, button press states are defined here...
#define BUTTON_PRESSED					LOW
#define BUTTON_NOT_PRESSED				HIGH


// Delay time between input scans/reads (in ms)...
#define DELAY_TIME_BETWEEN_INPUT_SCANS			50

// Bootup animation delay in ms (lower number makes the animations faster...
#define BOOTUP_ANIMATION_DELAY				150
#define BLUETOOTH_AWAITING_CONNECTION_ANIMATION_DELAY	200

#endif
