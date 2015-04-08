# PLAN

## Current
* Builder
** __Bugfix exectute/undo activate plug command (robot is prepared now)__
** __Fix orbit camera (?) -> inspect TrackballCamera from Polycode IDE__
** __Remove the entier Knob stuff from robot into Constructor/Display.cpp__
** __Add component but non active => robot must not delete or should signal the failed command somehow__ 
** __Simplify (remove Robot, use commands and model instead) (?)__
* __Display key and mouse action on screen.__
* Hold two lines where you display key, fade out in time
* Record/Replay (?)
** Split current robot into robot for simulation (updata) and model for construction (?)

## Futur
* POV Camera
* Robotic Components
** Morphing/Scripting block (?)
** Morphing/Inverter block
** Morphing/Averager block
** Morphing/Reducer block
** Active/Motor
** Passive/Soft block
** Passive/Weel
** Sensitive/Actor feedback
** Sensitive/Sinus signal generator 
* Physical simulation
** Use joints to hold the blocks together (?)
** Use joints to emulate motors (?)
** Terrain builder
** interaction
* Packages
** Ubunut pkgs
** Red Hat pkgs
** Apple pkgs
** Windows pkgs
