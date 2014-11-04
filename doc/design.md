# Design

## Precondition
* Physic library
* 3D Library


## Goal
Have a small set of shapes (mostly boxes)

## Namespace
::ch::game::synthetics

## Base Objects
::ch::game::synthetics::objects
SynObject
SynHub:SynObject
SynActor:SynHub
SynSensor:SynHub
SynMorph:SynHub
SynMotor:SynActor
SynDistance:SynSensor

## Graphic Objects
SynGraphic:SynObject
SynGlutBox:SynGraphic
SynDebugBox:SynGraphic
...

## Physic Objects
SynPhysic:SynObject
SynBulletBox:SynPhysic
...

## Coupling
A Base Object holds one or more graphic objcts and one physic object


