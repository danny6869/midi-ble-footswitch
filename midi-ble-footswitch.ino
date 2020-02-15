#include "config.h"
#include "MidiController.h"

// Create MIDI-BLE a controller object...
MidiController *controllerObj;

void setup() {

  // Set up serial communications for monitoring/debugging...
  Serial.begin(115200);
  Serial.println("Initializing");

  controllerObj = new MidiController(BLE_DEVICE_NAME);

  // Add all of our controls for this pedal...
  // 4 midi note buttons (input pins: 13, 15, 17, 19, led pins: 12, 14, 16, 18)
  controllerObj->addCCButton(13, 12, MIDI_CHANNEL_1, MIDI_CC_CONTROL_20);
  controllerObj->addCCButton(15, 14, MIDI_CHANNEL_1, MIDI_CC_CONTROL_21);
  controllerObj->addCCButton(17, 16, MIDI_CHANNEL_1, MIDI_CC_CONTROL_22);
  controllerObj->addCCButton(19, 18, MIDI_CHANNEL_1, MIDI_CC_CONTROL_23);

  // If you would rather have the buttons represent notes being played...
  //controllerObj->addNoteButton(19, 18, MIDI_CHANNEL_1, MIDI_NOTE_E3, BUTTON_PRESS_TYPE_MOMENTARY);
  //controllerObj->addNoteButton(19, 18, MIDI_CHANNEL_1, MIDI_NOTE_F3, BUTTON_PRESS_TYPE_MOMENTARY);
  //controllerObj->addNoteButton(19, 18, MIDI_CHANNEL_1, MIDI_NOTE_Gb3, BUTTON_PRESS_TYPE_LATCHING);
  //controllerObj->addNoteButton(19, 18, MIDI_CHANNEL_1, MIDI_NOTE_G3, BUTTON_PRESS_TYPE_LATCHING);

  // ...and 2 midi expression pedals (input pins: 2, and 3)
  controllerObj->addExpressionPedal(2, MIDI_CHANNEL_1, MIDI_CC_CONTROL_12, EXPRESSION_PEDAL_DIRECTION_LOW_TO_HIGH, EXPRESSION_PEDAL_CURVE_LINEAR);
  controllerObj->addExpressionPedal(3, MIDI_CHANNEL_2, MIDI_CC_CONTROL_13, EXPRESSION_PEDAL_DIRECTION_LOW_TO_HIGH, EXPRESSION_PEDAL_CURVE_LINEAR);

  // ...and while we are testing, setup the onboard button/led as a note button...
  //controllerObj->addNoteButton(6, 7, MIDI_CHANNEL_1, MIDI_NOTE_C3, BUTTON_PRESS_TYPE_LATCHING);

  controllerObj->start();

}

void loop()
{
  controllerObj->loop();
}
