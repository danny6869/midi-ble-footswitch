# Direction & Curve Types Constants

When adding an expression pedal with a call to
controllerObj->addNoteButton(), you can specify what direction the pedal
should move in, and what type of response curve you would like.

## Direction

- EXPRESSION_PEDAL_DIRECTION_LOW_TO_HIGH
  - This direction type causes the pedal to have a value of 0 when pulled back to the heel position, and 127/full when fully pressed down at the toe.

- EXPRESSION_PEDAL_DIRECTION_HIGH_TO_LOW
  - This direction will cause the values to reverse.  The pedal will have a value of 127/full when pulled back to the heel position, and 0 when fully pressed down at the toe.

## Curve Type

- EXPRESSION_PEDAL_CURVE_LINEAR
  - The linear type will cause the response of the pedal to be uniform across the whole range of movement.

- EXPRESSION_PEDAL_CURVE_ACCELERATED
  - The accelerated type will make the response of the pedal be slower at the heel position, and be faster as you approach the fully pressed position.

- EXPRESSION_PEDAL_CURVE_DECELERATED
  - The decelrates type will make the response of the pedal be faster at the heel end, and will be slower as you approach the fully pressed position.

## Direction / Curve Type Chart

This chart contains a visualization of each possible combination of direction/curve.

| Curve Type                         | Direction                              | Curve Shape                                    |
|:-----------------------------------|:--------------------------------------|:------------------------------------------------|
| EXPRESSION_PEDAL_CURVE_LINEAR      | EXPRESSION_PEDAL_DIRECTION_LOW_TO_HIGH | ![shape](curve-linear-normal.png)       |
| EXPRESSION_PEDAL_CURVE_ACCELERATED | EXPRESSION_PEDAL_DIRECTION_LOW_TO_HIGH | ![shape](curve-accelerated-normal.png)  |
| EXPRESSION_PEDAL_CURVE_DECELERATED | EXPRESSION_PEDAL_DIRECTION_LOW_TO_HIGH | ![shape](curve-decelerated-normal.png)  |
| EXPRESSION_PEDAL_CURVE_LINEAR      | EXPRESSION_PEDAL_DIRECTION_HIGH_TO_LOW | ![shape](curve-linear-reverse.png)      |
| EXPRESSION_PEDAL_CURVE_ACCELERATED | EXPRESSION_PEDAL_DIRECTION_HIGH_TO_LOW | ![shape](curve-accelerated-reverse.png) |
| EXPRESSION_PEDAL_CURVE_DECELERATED | EXPRESSION_PEDAL_DIRECTION_HIGH_TO_LOW | ![shape](curve-decelerated-reverse.png) |

