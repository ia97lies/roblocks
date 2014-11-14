//----------------------------------------------------------------------------
// Copyright 2014 Christian Liesch
// Provide under MIT License
//
//----------------------------------------------------------------------------

#include "Synthetics/Synthetics.h"

Synthetics::Synthetics()
  : BulletOpenGLApplication()
{
}

void Synthetics::InitializePhysics() {
  // create the collision configuration
  m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
  // create the dispatcher
  m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);
  // create the broadphase
  m_pBroadphase = new btDbvtBroadphase();
  // create the constraint solver
  m_pSolver = new btSequentialImpulseConstraintSolver();
  // create the world
  m_pWorld = new btDiscreteDynamicsWorld(m_pDispatcher, m_pBroadphase, m_pSolver, m_pCollisionConfiguration);

  CreateObjects();
}

void Synthetics::ShutdownPhysics() {
  delete m_pWorld;
  delete m_pSolver;
  delete m_pBroadphase;
  delete m_pDispatcher;
  delete m_pCollisionConfiguration;
}

void Synthetics::CreateObjects() {
  // create a ground plane
  CreateGameObject(new btBoxShape(btVector3(1,50,50)), 0, btVector3(0.2f, 0.6f, 0.6f), btVector3(0.0f, 0.0f, 0.0f));
  // create a border
  CreateGameObject(new btBoxShape(btVector3(2,1,51)), 0, btVector3(0.2f, 0.6f, 0.6f), btVector3(50.0f, 1.0f, 0.0f));
  CreateGameObject(new btBoxShape(btVector3(2,1,51)), 0, btVector3(0.2f, 0.6f, 0.6f), btVector3(-50.0f, 1.0f, 0.0f));
  CreateGameObject(new btBoxShape(btVector3(2,51,1)), 0, btVector3(0.2f, 0.6f, 0.6f), btVector3(0.0f, 1.0f, 50.0f));
  CreateGameObject(new btBoxShape(btVector3(2,51,1)), 0, btVector3(0.2f, 0.6f, 0.6f), btVector3(0.0f, 1.0f, -50.0f));

  // default obstacle
  CreateGameObject(new btBoxShape(btVector3(2,5,5)), 0, btVector3(0.2f, 0.6f, 0.6f), btVector3(10.0f, 1.0f, 10.0f));


  // create our red box, but store the pointer for future usage
  CreateGameObject(new btBoxShape(btVector3(1,1,1)), 1.0, btVector3(1.0f, 0.2f, 0.2f), btVector3(0.0f, 10.0f, 0.0f));

  // create a second box
  CreateGameObject(new btBoxShape(btVector3(1,1,1)), 1.0, btVector3(0.0f, 0.2f, 0.8f), btVector3(1.25f, 20.0f, 0.0f));

  // create two boxes connected with a join
  GameObject* obj1 = CreateGameObject(new btBoxShape(btVector3(1, 1, 1)), 1, btVector3(0.7f, 0.7f, 0.7f), btVector3(5.0f, 4.0f, -5.0f));
  GameObject* obj2 = CreateGameObject(new btBoxShape(btVector3(1, 1, 1)), 1, btVector3(0.7f, 0.7f, 0.7f), btVector3(10.0f, 4.0f, -5.0f));
  btTransform pivot1;
  pivot1.setIdentity();
  pivot1.setOrigin(btVector3(0, 1, 0));
  btTransform pivot2;
  pivot2.setIdentity();
  pivot2.setOrigin(btVector3(0, -1, 0));

  btGeneric6DofConstraint* constraint = new btGeneric6DofConstraint(*(obj1->GetRigidBody()), *(obj2->GetRigidBody()), pivot1, pivot2, true);
  constraint->setAngularLowerLimit(btVector3(0,0,0));
  constraint->setAngularUpperLimit(btVector3(0,0,0));
  m_pWorld->addConstraint(constraint, true);
}

