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
* __Record/Replay (just implement a event handler and also take dt in account)__
* Split current robot into robot for simulation (updata) and model for construction (?)!
-> For simulation in a physical enviroment we need a clear distinction between robot and builder
* Context Menu depending on object and its state (free, inplace, connected) (?)!!!
-> Problems here is how do I know what the context menu should display
-> I do not want to polute component with context menu knowledge
-> Build a context menu depending on robot state (empty, root, inplace, added)
-> ContextMenu 1 -> * ContextMenuEntry
-> ContextMenuEntry returns Command on click
-> ContextMenu on right click (or hoover?)
* Logger (in the long term I need a logger no question)(?)!!
-> Not sure how important as we have now record/play
-> No boiler plate or as little as possible
-> Configurable which part logs and how much (error, info, debug)
-> Not sure if Polycode::Logger fits my needs but this is used for start polycode already, so no choice I fear
* Bring robot in a physical enviroment (?)
-> Define joints for servo, linear
-> Hold the root element with a constrain
-> attach every component with joints
-> check the impackt of the huge number of collisions and how to avoid it

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
