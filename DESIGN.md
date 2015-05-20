# Design
## Robotic parts 
A robotic part consist of shapes and plugs.

### Plug
A plug is for orientation to plug another component and for the communication. A plug is eigther input, output, inout or deaf.
* Input green
* Output red
* Inout yellow
* Deaf black

### Component
The component is the blueprint to generate a node which contains the shape, the plugs as user data as well as physical control and the robotic control.
There will be a create method to construct the specific robotic part, actually it is a factory.

### Hub
A hub is the simplest component and the communication backbone. A hub consist of 5 inout and one deaf plug. A hub is a blue cube.

## Construction
A robot is constructed with robotic parts.
