#Synthetics
A robotics framework for easily assemble robots out of robotic components and run them in synthetic enviroment.

##Configuration
The configuration is a simple Lua script. Currently only the initial resolution can be set and the needed components can be loaded.

##Predefined Components
There will be a set of predefined components
* Passive.Hub
* Active.Servo
* Active.Motor
* Active.Linear
* Active.Light
* Sensor.Light
* Sensor.Distance
* Morph.Negator
* Morph.Average
* Morph.Trigger

##Components
Every component specifies its connect faces, event handler and shape. A component consist of parts and every part do have plugs (connecting faces).

### Part
A part do have plugs, which define the connectiong faces for the component. The first part is the parent of the others. only the first part can be used to plug into an existing robot.
Parts can be connected fix or with a joint. You can apply force and velocity to a joint or just set a given position which the join should hold.

### Plug
A plug defines the coordinate of the pluggable faces of a component.

##Custom Components
It is possible to implement own components as a shared C++ library as all existing components are as well shared libraries. All used components must be specified in the Resource/synthetics.conf. 

