#include "MidiExpressionPedal.h"
#include <Arduino.h>
#include <math.h>

// Maximum 10 bit value returned from analogRead...
static int _MAXIMUM_READ_VALUE    = pow (2, 10) - 1;
static int _MAXIMUM_MIDI_CC_VALUE = 127;

MidiExpressionPedal::MidiExpressionPedal( MidiBLEDevice * cMidiBleDevice, int cid, int cbutton_pin, int cmidi_channel, int cmidi_control_number, int cpedal_direction, int ccurve_type )
{
  id                  = cid;
  midiBleDevice       = cMidiBleDevice;
  button_pin          = cbutton_pin;
  midi_channel        = cmidi_channel;
  midi_control_number = cmidi_control_number;
  pedal_direction     = cpedal_direction;
  curve_type          = ccurve_type;
  last_midi_value     = 0;
}

int convertToMidiPositionLinear(int analog_input_value) {
  // Returns a midi position value (0-127) based on our analog input value (0-1023)...
  // Straight line on a graph
  // |    /
  // |   /
  // |  /
  // | /
  // |/_____
  int new_midi_value = int ( analog_input_value / _MAXIMUM_READ_VALUE * _MAXIMUM_MIDI_CC_VALUE );
  return new_midi_value;
}

int convertToMidiPositionAccelerated(int analog_input_value) {
  // Returns a midi position value (0-127) based on our analog input value (0-1023)...
  // Parabolic curve on a graph
  // |     .
  // |
  // |
  // |    .
  // |
  // |   .
  // |  .
  // |.______
  int new_midi_value = int ( pow(analog_input_value, 2) / pow(_MAXIMUM_READ_VALUE, 2) * _MAXIMUM_MIDI_CC_VALUE );
  return new_midi_value;
}

int convertToMidiPositionDecelerated(int analog_input_value) {
  // Returns a midi position value (0-127) based on our analog input value (0-1023)...
  // (sideways) Parabolic curve on a graph
  // |                    .
  // |          .
  // |    .
  // | .
  // |.__________
  int new_midi_value = int ( sqrt(analog_input_value) / sqrt(_MAXIMUM_READ_VALUE) * _MAXIMUM_MIDI_CC_VALUE );
  return new_midi_value;
}

void MidiExpressionPedal::handleState() {

  int analog_input_value = analogRead(button_pin);

  // Calculate what that translates to on our MIDI CC scale...
  int new_midi_value;
  switch (curve_type) {
    case EXPRESSION_PEDAL_CURVE_LINEAR:
      new_midi_value = convertToMidiPositionLinear(analog_input_value);
      break;
    case EXPRESSION_PEDAL_CURVE_ACCELERATED:
      new_midi_value = convertToMidiPositionAccelerated(analog_input_value);
      break;
    case EXPRESSION_PEDAL_CURVE_DECELERATED:
      new_midi_value = convertToMidiPositionDecelerated(analog_input_value);
      break;
    default:
      Serial.print("ERROR: Unknown value for expression pedal curve type: ");
      Serial.print(curve_type);
      Serial.println();
      break;
  }

  // Invert the direction if needed...
  if ( pedal_direction == EXPRESSION_PEDAL_DIRECTION_HIGH_TO_LOW ) {
    new_midi_value = _MAXIMUM_MIDI_CC_VALUE - new_midi_value;
  }

  if ( new_midi_value != last_midi_value ) {

    Serial.print("Input: ");
    Serial.print(analog_input_value);
    Serial.print("; MIDI Value: ");
    Serial.print(new_midi_value);
    Serial.print("; via Conversion: ");
    Serial.print(curve_type);
    Serial.print("; " + pedal_direction ? "(normal)" : "(reversed)");
    Serial.println();

    midiBleDevice->sendMIDIControlChange( midi_channel, midi_control_number, new_midi_value );

  } // else no change in state, nothing to update

  // Update our last known status so we can detect when it changes...
  last_midi_value = new_midi_value;
}

void MidiExpressionPedal::initGPIOPins() {
  /*
    Setup our button pin
  */
  pinMode(button_pin, INPUT);

}
void MidiExpressionPedal::resetState() {
  /* No-op for expression pedals */
}
