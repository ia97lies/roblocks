#Synthetics
A robotics framework for easily assemble robots out of robotic components and run them in synthetic enviroment.

##Configuration
The configuration is a simple Lua script. Currently only the initial resolution can be set and the needed components can be loaded.

##Components
Every component specifies its connect faces, event handler and shape.

##Predefined Components
* Passive.Hub
* Actor.Motor
* Actor.Servo
* Sensor.Light
* Sensor.Distance
* Morph.Negator
* Morph.Average

##Custom Components
It is possible to implement own components as a shared C++ library as all existing components are as well shared libraries. All used components must be specified in the Resource/synthetics.conf. 
