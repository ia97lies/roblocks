# PLAN

## Current
* __Bugfix exectute/undo activate plug command (robot is prepared now)__
* __Fix orbit camera (?) -> inspect TrackballCamera from Polycode IDE__
* __Remove the entier Knob stuff from robot into Constructor/Display.cpp__
* __Add component but non active => robot must not delete or should signal the failed command somehow__ 
* __Simplify (remove Robot, use commands and model instead) (?)__
* __Display key and mouse action on screen.__
* __Hold two lines where you display key, fade out in time__
* __Knobs have to be blue (better light blue)__
* __Refactor knob color setting and activation do it at one place as it is always the very same code.__
* Record/Replay (just implement a event handler and also take dt in account)
* Split current robot into robot for simulation (updata) and model for construction (?)
* Context Menu depending on object and its state (free, inplace, connected) (?)
* Logger (in the long term I need a logger no question)(?)

## Futur
* POV Camera
* Morphing/Scripting block (?)
* Morphing/Inverter block
* Morphing/Averager block
* Morphing/Reducer block
* Active/Motor
* Passive/Soft block
* Passive/Weel
* Sensitive/Actor feedback
* Sensitive/Sinus signal generator 
* Use joints to hold the blocks together (?)
* Use joints to emulate motors (?)
* Terrain builder
* interaction
* Ubunut pkgs
* Red Hat pkgs
* Apple pkgs
* Windows pkgs
* Random Monkey (press key and mouse randomly for testing purpose)
