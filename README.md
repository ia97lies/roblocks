# Synthetics
Lego like frameworke for easily assamble robots out of blocks and triagnles and run them in a synthetic enviroment.

## Components
A component specifies its connect faces, event handler and shape.

### Predefined Blocks
* Passive.Hub
* Actor.Motor
* Actor.Servo
* Sensor.Light
* Sensor.Distance
* Morph.Negator
* Morph.Average

### Custom Blocks
All blocks are shared libs which must be specified in the Resource/synthetics.conf therefor it is possible to implement custom blocks.
