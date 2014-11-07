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

## Coupling
A Base Object holds one or more graphic objcts and one physic object


