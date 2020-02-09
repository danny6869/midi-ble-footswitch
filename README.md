# Wireless Midi BLE Footswitch System

This software will allow you (with the proper hardware) to easily create a fully wireless Midi BLE pedal/footswitch system.  Out of the box, this software is configured for four footswitches, and two expression pedals.

Have a look at the demonstration video found here...
[![Demonstration Video](http://img.youtube.com/vi/HWy88jRTAKY/0.jpg)](http://www.youtube.com/watch?v=HWy88jRTAKY)

The lines that do that magic for you are found in [midi-ble-footwitch/midi-ble-footswitch.ino]

```
controllerObj.addButton(12, 11, MIDI_CHANNEL_1, 1, LATCHING_BUTTON_PRESSES);
controllerObj.addButton(14, 13, MIDI_CHANNEL_1, 2, LATCHING_BUTTON_PRESSES);
controllerObj.addButton(17, 16, MIDI_CHANNEL_1, 3, LATCHING_BUTTON_PRESSES);
controllerObj.addButton(19, 18, MIDI_CHANNEL_1, 4, LATCHING_BUTTON_PRESSES);
controllerObj.addExpressionPedal(2, MIDI_CHANNEL_1, 0);
controllerObj.addExpressionPedal(3, MIDI_CHANNEL_2, 0);
```


|          | Input Pin | LED Pin | Midi Channel | Midi Note | Midi Note # | Type     |
|----------|:---------:|:-------:|:------------:|:---------:|:-----------:|:--------:|
| Button 1 | xx        |         | 1            | E3        | 52          | Latching |
| Button 2 | xx        |         | 1            | F3        | 53          | Latching |
| Button 3 | xx        |         | 1            | F#3       | 54          | Latching |
| Button 4 | xx        |         | 1            | G3        | 55          | Latching |
| Expr. 1  | xx        | -       | 1            | -         | -           | Linear   |
| Expr. 2  | xx        | -       | 2            | -         | -           | Linear   |



## Parts

- 4 tactile switches
- 3mm LEDs
  - 1 green
  - 1 red
  - 4 white
- Sparkfun Buletooth/BLE Breakout Board (or any other compatible)
  - Model: WRL-13990
  - Available [here](https://www.digikey.ca/product-detail/en/sparkfun-electronics/WRL-13990/1568-1449-ND/6562783)


## Hardware Requirements

This software was specifically written to work with a sparkfun nRF52832 (bluetooth/ble) breakout board.





You can download the 3D STL files to print from thingiverse [here](https://www.thingiverse.com/thing:4134488).


## Special Thanks

### [DigiKey](https://www.digikey.ca)

- Website: https://www.digikey.ca
- Thanks to [DigiKey](https://www.digikey.ca) for having a great online store, with a huge selection, and more importantly, for saving me a ton of time by providing a [great tutorial](https://www.digikey.ca/en/maker/projects/midi-ble-tutorial/6964435cd2854ed1856aeb7b177312c3) for doing basic MIDI BLE communication.

### [The Midi Association](https://www.midi.org/)

- Website: https://www.midi.org/
- Thanks to [The Midi Association](https://www.midi.org/) for creating a protocol that is well documented, and has stood the test of time, and moved into the 21st century (with the [Bluetooth LE MIDI Specification](https://www.midi.org/specifications/item/bluetooth-le-midi)).
