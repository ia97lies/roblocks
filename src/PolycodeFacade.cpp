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

  void PolycodeFacade::trackCollisionEntity(Polycode::Entity *entity) {
    m_scene->trackCollision(entity);
  }

  void PolycodeFacade::trackPhysicsEntity(Polycode::Entity *entity, float mass) {
    // TODO: is it possible to get shape type by entity some how?
    //       currently everything is threaded as a box, maybe this is sufficent
    m_scene->trackPhysicsChild(entity, PhysicsSceneEntity::SHAPE_BOX,  mass);
  }

  void PolycodeFacade::removeEntity(Polycode::Entity *entity) {
    m_scene->removeEntity(entity);
  }
}

