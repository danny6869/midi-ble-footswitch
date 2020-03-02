# Configuring your device

There are two files that need to be modified to customize the software for how you would like it to behave.

## [config.h](config.h)

Have a look at the configurations found in that file, and adjust as you see fit.  The defaults do not need to be adjusted unless you are using different hardware than what is described here.

## [midi-ble-footswitch.ino](midi-ble-footswitch.ino)

This is the main program's entry point, and is where the software is setup for your preferred hardworad configuration.  Listed below are the defaults, and possible adjustments you can easily make on your own if customizing.  Again, if you are following this guide, you can leave everything as it is by default.

The lines that do that magic for you are found in [../midi-ble-footwitch/midi-ble-footswitch.ino]

#### Midi Control Change Buttons (default)

These types of buttons send a CC ON when pressed.

```
  controllerObj->addCCButton(13, 12, MIDI_CHANNEL_1, MIDI_CC_CONTROL_20);
  controllerObj->addCCButton(15, 14, MIDI_CHANNEL_1, MIDI_CC_CONTROL_21);
  controllerObj->addCCButton(17, 16, MIDI_CHANNEL_1, MIDI_CC_CONTROL_22);
  controllerObj->addCCButton(19, 18, MIDI_CHANNEL_1, MIDI_CC_CONTROL_23);
```
| Button # | Input Pin | LED Pin | Midi Channel | Midi Control # |
|:--------:|:---------:|:-------:|:------------:|:--------------:|
| 1        | 13        | 12      | 1            | 20             |
| 2        | 15        | 14      | 1            | 21             |
| 3        | 17        | 16      | 1            | 22             |
| 4        | 19        | 18      | 1            | 23             |

* See MidiProtocol.h for MIDI_* constants

#### Midi Control Change / Expression Pedal

This type of control will transmit CC messages with a value of 0-127 depending on the position of the pedal.

```
  controllerObj->addExpressionPedal(2, MIDI_CHANNEL_1, MIDI_CC_CONTROL_12, EXPRESSION_PEDAL_DIRECTION_LOW_TO_HIGH, EXPRESSION_PEDAL_CURVE_LINEAR);
  controllerObj->addExpressionPedal(3, MIDI_CHANNEL_2, MIDI_CC_CONTROL_13, EXPRESSION_PEDAL_DIRECTION_LOW_TO_HIGH, EXPRESSION_PEDAL_CURVE_LINEAR);
```

| Pedal # | Input Pin | Midi Channel | Midi Control # | Direction   | Curve Type |
|:-------:|:---------:|:------------:|:--------------:|:-----------:|:----------:|
| 1       | 2         | 1            | 12             | Low to High | Linear     |
| 2       | 3         | 2            | 13             | Low to High | Linear     |

* See the [curve type reference chart](reference-pedal-curves.md) for details on the different curve types available

_WARNING: If you are not going to be hooking up expression pedal jacks, then comment out all addExpressionPedal() lines in [midi-ble-footswitch.ino](midi-ble-footswitch.ino).  (if the jacks are not hooked up, then the signal for these will be reported as off/0 ... which will surely cause you problems)_



#### Midi Note Buttons (non-default/optional)

These types of buttons send basic NOTE ON/OFF commands when pressed.  If the button is setup as momentary, then  it will send a NOTE ON when the button is pressed down, and a NOTE OFF when it is released.  If the button is setup as a latching type, then it will send alternating NOTE ON and NOTE OFF messages with each press.

```
  controllerObj->addNoteButton(19, 18, MIDI_CHANNEL_1, MIDI_NOTE_E3, BUTTON_PRESS_TYPE_MOMENTARY);
  controllerObj->addNoteButton(19, 18, MIDI_CHANNEL_1, MIDI_NOTE_F3, BUTTON_PRESS_TYPE_MOMENTARY);
  controllerObj->addNoteButton(19, 18, MIDI_CHANNEL_1, MIDI_NOTE_Gb3, BUTTON_PRESS_TYPE_LATCHING);
  controllerObj->addNoteButton(19, 18, MIDI_CHANNEL_1, MIDI_NOTE_G3, BUTTON_PRESS_TYPE_LATCHING);
```

| Button # | Input Pin | LED Pin | Midi Channel | Midi Note | Midi Note # | Type      |
|:--------:|:---------:|:-------:|:------------:|:---------:|:-----------:|:---------:|
| 1        | 13        | 12        | 1            | E3        | 52        | Momentary |
| 2        | 15        | 14        | 1            | F3        | 53        | Momentary |
| 3        | 17        | 16        | 1            | Gb3       | 54        | Latching  |
| 4        | 19        | 18        | 1            | G3        | 55        | Latching  |

* See MidiProtocol.h for MIDI_* constants

