//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_POLYCODE_FACADE_H
#define SYNTHETICS_POLYCODE_FACADE_H

#include "Polycode.h"
#include "Polycode3DPhysics.h"

namespace Synthetics {
  class PolycodeFacade {
    public:
      PolycodeFacade(Polycode::Core *core, Polycode::PhysicsScene *scene); 
      virtual ~PolycodeFacade();

      virtual void addEntity(Polycode::Entity *entity);
      virtual void removeEntity(Polycode::Entity *entity);
      virtual void trackCollisionEntity(Polycode::Entity *entity);
      virtual void removeCollisionEntity(Polycode::Entity *entity); 
      virtual void trackPhysicsEntity(Polycode::Entity *entity, float mass);
      virtual void removePhysicsEntity(Polycode::Entity *entity);
      virtual Polycode::PhysicsHingeConstraint *createHingeConstraint(Polycode::Entity *entity);
      //XXX => virtual Polycode::PhysicsHingeConstraint *getPhysicsHinge(

    private:
      Polycode::Core *m_core;
      Polycode::PhysicsScene *m_scene;
  };
}

#endif
