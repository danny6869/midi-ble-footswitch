#include "config.h"
#include "MidiController.h"

// Create MIDI-BLE a controller object...
MidiController *controllerObj;

void setup() {

  // Set up serial communications for monitoring/debugging...
  Serial.begin(115200);
  delay(500);

  Serial.println("Program Started");

  controllerObj = new MidiController(BLE_DEVICE_NAME);

  // Add all of our controls for this pedal...
  // 4 midi note buttons (input pins: 12, 14, 17, 19, led pins: 11, 13, 16, 18)
  controllerObj.addButton(12, 11, MIDI_CHANNEL_1, MIDI_NOTE_E3, BUTTON_PRESS_TYPE_LATCHING);
  controllerObj.addButton(14, 13, MIDI_CHANNEL_1, MIDI_NOTE_F3, BUTTON_PRESS_TYPE_LATCHING);
  controllerObj.addButton(17, 16, MIDI_CHANNEL_1, MIDI_NOTE_Gb3, BUTTON_PRESS_TYPE_LATCHING);
  controllerObj.addButton(19, 18, MIDI_CHANNEL_1, MIDI_NOTE_G3, BUTTON_PRESS_TYPE_LATCHING);
  // ...and 2 midi expression pedals (input pins: 2, and 3)
  controllerObj.addExpressionPedal(2, MIDI_CHANNEL_1, EXPRESSION_PEDAL_DIRECTION_LOW_TO_HIGH, EXPRESSION_PEDAL_CURVE_LINEAR);
  controllerObj.addExpressionPedal(3, MIDI_CHANNEL_2, EXPRESSION_PEDAL_DIRECTION_LOW_TO_HIGH, EXPRESSION_PEDAL_CURVE_LINEAR);

  // ...and while we are testing, setup the onboard button/led as a note button...
  controllerObj->addButton(6, 7, MIDI_CHANNEL_1, MIDI_NOTE_C3, BUTTON_PRESS_TYPE_LATCHING);

  controllerObj->start();

}

void loop()
{
  controllerObj->loop();
}
