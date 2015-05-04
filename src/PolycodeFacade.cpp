//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolycodeFacade.hpp"

using namespace Polycode;

namespace Synthetics {
  PolycodeFacade::PolycodeFacade(Polycode::Core *core, Polycode::PhysicsScene *scene) {
    m_core = core;
    m_scene = scene;
  }

  PolycodeFacade::~PolycodeFacade() {}

  void PolycodeFacade::addEntity(Polycode::Entity *entity) {
    m_scene->addEntity(entity);
  }

  void PolycodeFacade::removeEntity(Polycode::Entity *entity) {
    m_scene->removeEntity(entity);
  }

  void PolycodeFacade::trackCollisionEntity(Polycode::Entity *entity) {
    m_scene->trackCollision(entity);
  }

  void PolycodeFacade::removeCollisionEntity(Polycode::Entity *entity) {
    m_scene->removeCollision(entity);
  }

  void PolycodeFacade::trackPhysicsEntity(Polycode::Entity *entity, float mass) {
    m_scene->trackPhysicsChild(entity, PhysicsSceneEntity::SHAPE_BOX,  mass);
  }

  void PolycodeFacade::removePhysicsEntity(Polycode::Entity *entity) {
    m_scene->removePhysicsChild(entity);
  }

  PhysicsHingeConstraint *PolycodeFacade::createHingeConstraint(Polycode::Entity *entity) {
    return m_scene->createHingeConstraint(entity, Vector3(0,0,0), Vector3(0,1,0), 0, 0);
  }
}

