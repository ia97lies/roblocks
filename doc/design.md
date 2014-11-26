# Design

## Precondition
* A build Polycode

## Goal
Have a small set of shapes (mostly blocks) and make them easily plugable like lego bricks.
The blocks are hub like elements which build up a communication bus between all components.

## Sandbox
To run Synthetics I propse a sandbox like system which contains everything. The rought structure looks like that
/
/bin
/lib
/Resources

A run script is placed in the root folder of this sandbox. All executable can be found in "bin" and all plugins in "lib". The "Resource" folder holds the mesh and stuff.

## Namespace
::ch::game::synthetics

## Units
A unit is a construction block to build up the robot. To be able to extent that, the base needs 2 things:
* A base unit with all possible operation for such a unit
* Loadable

To reach this goal I decided to use Lua as the configuration language. The configuration file is located in the Resource folder. To load a new unit type the Lua "require" command is used. The so must be placed either in the executable location "bin" or in the library folder "lib".

## Simulation
The blocks which are plugged do need as well simulation and visualization as well (colouring and the like).
There is not only physic simulation but also sensor simulation and its propagation to the actors.


