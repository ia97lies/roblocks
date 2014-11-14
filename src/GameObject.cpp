//----------------------------------------------------------------------------
// Copyright 2014 Christian Liesch
// Provide under MIT License
//
//----------------------------------------------------------------------------

#include "Synthetics/GameObject.h"

//----------------------------------------------------------------------------
GameObject::GameObject(
    btCollisionShape* pShape, 
    float mass, 
    const btVector3 &color, 
    const btVector3 &initialPosition, 
    const btQuaternion &initialRotation
) 
{
  m_selected = false;
  m_pShape = pShape;
  m_color = color;

  btTransform transform;
  transform.setIdentity();
  transform.setOrigin(initialPosition);
  transform.setRotation(initialRotation);
  m_pMotionState = new OpenGLMotionState(transform);

  btVector3 localInertia(0,0,0);
  if (mass != 0.0f) {
    pShape->calculateLocalInertia(mass, localInertia);
  }

  btRigidBody::btRigidBodyConstructionInfo cInfo(mass, m_pMotionState, pShape, localInertia);

  m_pBody = new btRigidBody(cInfo);
}

//----------------------------------------------------------------------------
GameObject::~GameObject() 
{
  delete m_pBody;
  delete m_pMotionState;
  delete m_pShape;
}

