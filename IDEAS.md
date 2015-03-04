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
* Real life blocks with stuff from ali express and some nano arduinos.

## Features
* Made "in place" components replacebale be just scroll through the components in the select screen *DONE*
* Loudspeaker would be cool, expecialy with the positional sound feature in polycode. *DONE*
* Store robot as a lua script *DONE*
* If it is possible to implement a microfon as a sensor?
* Add elastic blocks.
* LED (light in all direction) with connect faces in all direction
* Stretch a signal if more than one component (mapping the 0..100 signal to the rest of the range you have)

## Simulation
* Simulate signal propagation (see DESIGN.md) *DONE*

## Known Issues
### Rotate "in place" components
  - Not working if I will rotate over a childs plug orthogonal, it rotates then over parent.
  - Move to rotation axis to child tha may solve that problem
