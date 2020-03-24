# Wireless Midi BLE Footswitch System

This software will allow you (with the proper hardware) to easily create a fully working wireless Midi BLE pedal/footswitch system.  Out of the box, this software is configured for four footswitches, and two expression pedals.

WARNING: If you decide to customize, and NOT have expression pedal jacks, then be sure to comment out the two addExpressionPedal() lines in [midi-ble-footswitch.ino](midi-ble-footswitch.ino) or make sure the device you are using will not use the expression pedals.  (as they will be reported as being in position 0, which can cause you grief if configured to control volume for example)

Have a look at the demonstration video found here to see one in action...
[![Demonstration Video](http://img.youtube.com/vi/HWy88jRTAKY/0.jpg)](http://www.youtube.com/watch?v=HWy88jRTAKY)


## Hardware Requirements

This software was specifically written to work with a sparkfun nRF52832 (bluetooth/ble) breakout board.  (see the [parts list](README/parts-list.md) for exact details)

### Cheaper BLE Microcontroller Boards

There are other cheaper nRF52832 boards on the market, and my adventure actually started with those, however, they did not allow access to the BLE chipset at a low enough level, so I couldn't get it to report itself as a proper MIDI BLE device.

Until I figure out how to reflash those boards to allow that low level access, the sparkfun board will have to do.


## HOW-TO Build Your Own

You can follow the instructions found here to build your own 4 button / 2 expression wireless midi footswitch system, or just use this as a guide to get on your way building your own custom hardware configuration.

This software was purposely created so that customizations would only need to be done in a few places to satisfy 99.999993% of cases.

If you come up with any improvements, please consider contributing to this project on [github](https://github.com/danny6869/midi-ble-footswitch), or on [thingiverse](https://www.thingiverse.com/thing:4134488).

### Instructions

Before beginning, you need to decide if you are going to make the default 4 button, 2 expression pedal footswitch, or some other customized configuration.

If you are creating the default, then just follow the instructions below exactly, otherwise, you will have to take care to adjust the instructions in each step for the hardware confuguration of your choice.

If you just want to play around with the software on the Sparkfun BLE Board, then you should only need to follow steps [#2](README/software-configuration.md), and [#3](README/updating-the-microcontroller.md).

1. [Gather together all parts, and tools](README/parts-list.md)
   - 3D Printed Chassis/Case
   - Electronic Components
   - Tools
2. [Configure the software](README/software-configuration.md)
3. [Update the microcontroller using the Arduino IDE](README/updating-the-microcontroller.md)
   - Setting up the Arduino IDE
   - Updating the Sparkfun Board
   - Testing and Debugging
4. Solder components
   - [Power/charging circuit (switch/battery/LEDs)](README/howto-solder-power-and-charging-circuit.md)
   - [Buttons (and LEDs)](README/howto-solder-button-circuit.md)
   - (optional) [Expression Pedal Jacks](README/howto-solder-expression-pedal-jacks.md)
   - [Microcontroller Connectors](README/howto-solder-microcontroller-board.md)
5. [Final Assembly](README/final-assembly.md)

## Resources & Thanks

### [DigiKey](https://www.digikey.ca)

- Website: https://www.digikey.ca
- Thanks to [DigiKey](https://www.digikey.ca) for having a great online store, with
  a huge selection, and more importantly, for saving me a ton of time by providing
  a [great tutorial](https://www.digikey.ca/en/maker/projects/midi-ble-tutorial/6964435cd2854ed1856aeb7b177312c3)
  for doing basic MIDI BLE communication.

### [The Midi Association](https://www.midi.org/)

- Website: https://www.midi.org/
- Thanks to [The Midi Association](https://www.midi.org/) for creating a protocol
that is well documented, and has stood the test of time, and moved into the 21st
century (with the [Bluetooth LE MIDI Specification](https://www.midi.org/specifications/item/bluetooth-le-midi)).

### [HyVibe Guitars](https://www.hyvibe.audio/smart-guitar/)

- Website: https://www.hyvibe.audio/smart-guitar/
- Thanks to HyVibe for creating a great acoustic guitar that provided the inspiration for this project.  It's a great guitar with a great technology inside, and having a wireless midi pedal to use with it is awesome!  (especially for the looper)

### [Desmos Graphing Calculator](https://www.desmos.com/calculator)
- Website: https://www.desmos.com/calculator
- I used this online tool quite a bit during the creation of this readme.

## Note from the Creator

I strontly believe that things like this should be freely available on the internet, but I also believe that appreciation should be shown if you get use out of it, or find it useful at all.

If you feel so inclined, go click "like" on the thingiverse page (at the very least), or make a small donation...

[![Donate](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=QGM9ZGJDVFDEA)

...thanks, and happy printing/hacking!!!

