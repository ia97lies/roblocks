# Synthetics
A simulator to easily build and run robots. No programming is needed but possible. There are a set of components to plug your robots together. Every component do have a couple of faces to plug other components. There are router and hubs as well as morphing components to manipulate the signals of sensors.

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
