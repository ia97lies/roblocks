# Synthetics
Lego like frameworke for easily assamble robots out of blocks and triagnles and run them in a synthetic enviroment.

## Units
A unit specifies its connect faces and event handler. Unit events can send a value do the units. The value is a 3D vector. Maybe I should as well add a power line for more realistic simulations.
### Predefined Blocks
* Neutral.Block
* Neutral.Triangle
* Actor.Motor
* Actor.Servo
* Sensor.Light
* Sensor.Distance
* Morph.Negator
* Morph.Average
### Custom Blocks
All blocks are shared libs which must be specified in the Resource/synthetics.conf therefor it is possible to implement custom blocks.
