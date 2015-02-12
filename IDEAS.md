# IDEAS!!!
## Nameings
* Synthetics (current working name)
* RobotThings
* rThings
* ArtificalThings

## Interacting with your robot
* Combine your pc cameras input with a sensor to interact with our robot, like in real world :) 
  For example you can use real lamp and point to camera which is linked with a simulated light sensor.
  (Idea from Marc Liesch)
* Or combine a arduino with the virtual robot to test various sensors from outside world, like you would do with a real robot (touch sensors, point ligth, ...).

## General
* Sensors and actors should be combinable in one component
** Interactive LED field would need LEDs with combined approximity sensor
** Actors should as well act as sensors (feedback)
* Actors should transport Signals as well (maybe with a time shift)
* Real life blocks with stuff from ali express and some nano arduinos.

## Features
* Loudspeaker would be cool, expecialy with the positional sound feature in polycode. *DONE*
* If it is possible to implement a microfon as a sensor? *OPEN*
* Add elastic blocks.
* Store robot as a lua script
** add a Lua interface for Robot.hpp
** Also complex generated robots are possible (genetical algorithmen for example)
** The format of a stored robot is human readable and therefor easily extentable
** As well grouping of macro robot parts are that way possible.
** LED (light in all direction) with connect faces in all direction

## Simulation
* Simulate signal propagation as follow:
  - Every component have to register (in/out)
  - Iterate through all components
    - Every component hands the value in register "out" to its neighbours
      - transform the out signal depends on its implementation
    - Every component stores and cumulate the values from his neighbours in "in"
      - how to cumulate depends on its implementation
  - Do this on every update (hopefully we are this way fast enough)
    - if simulation runs with 60 Hz a signal will propagate 60 elements per second
  - Sensors are value sources
    - Have only outputs (Plug can be output input or both)
  - Actors are value sinks (and depending of its implementation as well sources or propagators)
    - Have at least on input and may have outputs
  - An output only can send signals to an input (actually the receiving plug should drop a signal if he is an output)

## Known Issues
### Rotate an object in "place" mode
  - Not working if I will rotate over a childs plug orthogonal, it rotates then over parent.
  - Move to rotation axis to child tha may solve that problem
