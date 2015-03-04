# Knowhow

A collection of stuff I need for pyhsics, simulation, graphics and io

## Physics
It seems that Polycode do not have a finish interface for 3D physics yet. The workaround of polycode for this lack is providing the bullet structurs, so people can directly call bullet lib methods/functions. I will figure out what I need and maybe try to feedback this to polycode project.

### Hinge Constrain

Code Sample:

```C++
  ...

  PhysicsScene *scene = new PhysicsScene();

  ScenePrimitive *ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 10, 10);
  ground->loadTexture("Resources/green_texture.png");
  scene->addPhysicsChild(ground, PhysicsSceneEntity::SHAPE_PLANE, 0.0);

  ScenePrimitive *box1 = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.5,0.5,0.5);
  box1->loadTexture("Resources/pink_texture.png");
  box1->setPosition(0,2,0);
  scene->addPhysicsChild(box1, PhysicsSceneEntity::SHAPE_BOX, 1.0);

  ScenePrimitive *box2 = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.5,0.5,0.5);
  box2->loadTexture("Resources/pink_texture.png");
  box2->setPosition(1,1,0);
  box1->addChild(box2);
  scene->trackPhysicsChild(box2, PhysicsSceneEntity::SHAPE_BOX, 1.0);

  // PhysicsHingeConstraint *createHingeJoint(Entity *entity1, Entity *entity2, Vector3 pivot1, Vector3 axis1, Vector3 pivot2, Vector3 axis2, Number minLimit, Number maxLimit);
  PhysicsHingeConstraint *constrain = scene->createHingeJoint(box1, box2, Vector3(0,0,0), Vector3(0,1,0), Vector3(-1,0,0), Vector3(0,1,0), 0, 270);
  constrain->btConstraint->enableAngularMotor(true, 1, 1);

  ...
```C++

ASCII simple drawing to show the idea of the two pivots, which are just some invisble arms

  box1 == pivot 1 =>axis1 axis2 <== pivot 2 == box2

The sample above mades the box1 the body and box2 the orbiter, perfekt for my servo.
Hinge also can be used to made stiff connections by setting the min and max limit to 0.

The limit is in radians instead of degrees (like most function in polycode use degrees not radians).
  
