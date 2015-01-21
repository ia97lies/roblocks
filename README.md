#Synthetics
A robotics framework for easily assemble robots out of robotic components and run them in synthetic enviroment.
The simulation is based on Polycode (see http://polycode.org).

##Configuration
The configuration is a simple Lua script. Currently only the initial resolution can be set and the needed components can be loaded.

##Predefined Components
There will be a set of predefined components
* Passive.Hub
* Active.Servo
* Active.Motor
* Active.Linear
* Active.Light
* Active.Loudspeaker (not yet done)
* Sensor.Light (not yet done)
* Sensor.Distance (not yet done)
* Morph.Negator (not yet done)
* Morph.Average (not yet done)
* Morph.Trigger (not yet done)

##Components
Every component specifies its connect faces, event handler and shape. A component consist of parts and every part do have plugs (connecting faces).

### Part
A part do have plugs, which define the connectiong faces for the component. The first part is the parent of the others. Only the first part can be used to plug into an existing robot.
Parts can be connected fix or with a joint. You can apply force and velocity to a joint or just set a given position which the join should hold.

### Plug
A plug defines the coordinate of the pluggable faces of a component.

##Custom Components
It is possible to implement own components as a shared C++ library as all existing components are as well shared libraries. All used components must be specified in the Resource/synthetics.conf. 

## Acknowledgements
I'd like to acknowledge the work of the following people or group:

* The Polycode framework from Ivan Safrin

## License
Synthetics is available under the MIT license.

