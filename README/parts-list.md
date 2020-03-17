# Parts and Tools


## 3D Printed Chassis/Case

You can download the 3D STL files to print from thingiverse [here](https://www.thingiverse.com/thing:4134488).


## Electronic Components


### General/Shared Parts

- Stranded Wire
  - 24 gauge
  - Optional: different colors
  - [Available on Amazon](https://www.amazon.ca/gp/product/B01KQ0D3M0)
  - WARNING: Use solid core wire at your own risk.  I did, and I regretted it every step of the way.

- 5 x 330ohm Resistors
  - [Available on Amazon](https://www.amazon.ca/dp/product/B07FYJFLL8)

- 6 x LEDs (3mm)
  - 4 x White (footswitch)
  - 1 x Red (power indicator)
  - 1 x Green (charging indicator)
  - [Available on Amazon](https://www.amazon.ca/gp/product/B01LYLN77H)

- Small crimp connectors
  - Assorted connectors [avalaible on Amazon](https://www.amazon.ca/gp/product/B0188DMF3A)
    - 2 x sets of male/female 5-conductor connectors (for each pair of buttons)
    - 1 x set of 2-conductor male/female connectors (for power)
    - 1 x set of male/female 4-conductor connectors (for each pair of expression pedal jacks)
  - JST connectors [available on Amazon](https://www.amazon.ca/gp/product/B0188YKCFC)
    - 1 x male 2-conductor (JST) connector (for LiPo)

- 4 x Small zip-ties for internal wire management

- 4 x Rubber stick-on anti-slip feet


### Microcontroller Board and Programmer
- Microcontroller
  - Sparkfun BLE Breakout Board
    - Model: WRL-13990 (nRF52832)
    - [Avaliable at DigiKey](https://www.digikey.ca/product-detail/en/sparkfun-electronics/WRL-13990/1568-1449-ND/6562783)
  - See the [Hardware Requirements](../README.md#Hardware%20Requirements) on the [Main Page](../README.md#Hardware%20Requirements) to see why this board was selected.  Deviate at your own risk.

- Microcontroller Programmer
  - Any USB to TTL Serial Adapter Module will do
  - Make sure it can support supplying 3.3v for programming the sparkfun microcontroller board
  - [Available on Amazon - FT232RL](https://www.amazon.ca/gp/product/B01JG8H5U4)


### Power/Charging Components

- LiPo Charging Circuit
  - 17mm x 27mm
  - [Available on Amazon - 18650](https://www.amazon.ca/gp/product/B07CCGVJ79)

- Power regulator circuit
  - [Available on Amazon - T64](https://www.amazon.ca/gp/product/B07L3RMJQB)

- Pushbutton switch
  - 7mm x 7mm
  - [Available on Amazon](https://www.amazon.ca/gp/product/B06XR8SQG9)

- LiPo Battery
  - 800maH (at maximum draw, about 8h, in reality at least double that)
  - 44mm x 24mm x 9mm
  - [Available on Amazon - B01N74TTW6](https://www.amazon.ca/gp/product/B01N74TTW6)


### Button Components

- 4 x Tactile switches
  - 6mm x 6mm x 5mm
  - [Avaialble at Adafruit](https://www.adafruit.com/product/367)
  - [Available at Amazon](https://www.amazon.ca/dp/product/B078HL5CC7)

- 4 x White 3mm LEDs

- 4 x 330 ohm resistors


### Expression Pedal Ports (optional)

- 2 x 1/4" stereo jacks with ring shunt (one per expression pedal port)
  - [Available as Next-Gen Guitars](https://nextgenguitars.ca/products/switchcraft-14b-1-4-stereo-jack-with-tip-ring-shunts.html)
  - The ring shunt is required do that the unit can know if an expression pedal is actually plugged in or not.  (so no expression pedal positions get reported when no pedal present)
  - WARNING: See the warning at the top of the main [README](../README.md) if you opt-out of having the expression pedal jacks in your configuration.


## Tools

- Soldering equipment
  - Soldering iron
  - Solder (good quality - for electronics)
  - Solder flux/paste (optional)
    - apply a small amount to wire/components before soldering
- Multimeter/Tester

- Thin (2-3mm?) heat-shrink tubing to keep things neat and tidy

