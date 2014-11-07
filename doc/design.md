# Design

## Precondition
* Physic library
* 3D Library


## Goal
Have a small set of shapes (mostly blocks) and make them easily plugable like lego bricks.
The blocks are hub like elements which build up a communication bus between all components.

## Namespace
::ch::game::synthetics

## Base Objects
::ch::game::synthetics::objects
Object
Hub:Object
Actor:Hub
Sensor:Hub
Morph:Hub
Motor:Actor
Distance:Sensor

## Graphic Objects
Graphic:Object
GlutBox:Graphic
DebugBox:Graphic
...

## Physic Objects
Physic:Object
BulletBox:Physic
...

## PhysicEngine
PhysicEngine:Object
BulletEngine:PhysicEngine

## Coupling
* A Base Object holds one or more graphic objcts and one physic object
* A physic object needs a corresponding physic engine implementation.
=> Try to make the physic engine interchangeable. Maybe worth a try.

## Simulation
The blocks which are plugged do need as well simulation and visualization as well (colouring and the like).
There is not only physic simulation but also sensor simulation and its propagation to the actors.


