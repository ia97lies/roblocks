# Design

## Precondition
* Physic library
* 3D Library


## Goal
Have a small set of shapes (mostly boxes)

## Namespace
::ch::game::synthetics

## Objects Hirarchie
::ch::game::synthetics::objects
SynObject
SynStatic:SynObject
SynBox:SynStatic
SynActor:SynBox
SynSensor:SynBox
SynMorph:SynBox
SynMotor:SynActor
SynDistance:SynSensor

## Graphical Interface

## Physics

