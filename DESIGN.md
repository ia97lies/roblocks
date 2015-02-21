# Synthetics Design

## Build System
### Component
The component can be a servo, motor, sensor, hub, router, negator, ...
A component can hold serveral other components. An added comonent is a child. This is only used for build the robot and to destruct it.

### Part
A component consist of one or more parts like body, hinge, knob, ...
The first part is the mother of all others.

### Plug
Every Part has zero or more plugs. Components can only be connected with those plugs.
A plug has a direction like Input, Output, InOut or Deaf to handle the signal flow from sensors to actors over several components.
The signal bus is the body and the direction is given by the connected plugs.
Every plug knows his component and his connected oposide plug.

## Signal Flow
### Sources, Propagators and Sinks
A sensor is a signal source. A sensor have at least one output plug.
An actor is a signal sink. An actor have at least one input plug.
A passive element is a signal propagator and manipulator. A passive element normaly has at least on inout plug.

### Inner state of an element
* Check all plugs and the connected plugs to calculate the inner value
** InOut+Output plug increase the inner value by the value from the output.
** Input+Output plug increase the inner value by the value form the output.
** Input+InOut plug increase the inner value by the value from the InOut.
** InOut+InOut plug increase the inner value by the value from the InOut.

* Then we have to set all our plugs to the new value
** InOut+InOut plug our InOut plug is set the the value - the value from oponent (else the overal value of the robot is increasing in every step)
** All other plugs just get the calculated inner value.

