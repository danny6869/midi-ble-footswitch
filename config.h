#pragma once
#include <Arduino.h>

#ifndef DCONFIG_H
#define DCONFIG_H

/*
   Configurations
*/

// Device name as seen in your bluetooth devices...
// TODO: Document max chars --- 20 I think!?
#define BLE_DEVICE_NAME         "Midi BLE Pedal 3D"

// Channel number for all controls...
#define CHANNEL_NUMBER          1

// Some micro-controllers have these reversed (much to my surprise), so the
// code will honour this for LED on/off commands...
#define LED_ON LOW
#define LED_OFF HIGH

// Bootup animation delay in ms (lower number makes the animations faster...
#define BOOTUP_ANIMATION_DELAY 150
#define BLUETOOTH_AWAITING_CONNECTION_ANIMATION_DELAY 200

#endif
