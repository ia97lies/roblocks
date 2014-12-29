//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolycodeFacade.hpp"

namespace Synthetics {
  PolycodeFacade::PolycodeFacade(Polycode::Core *core, Polycode::CollisionScene *scene) {
    m_core = core;
    m_scene = scene;
  }

  PolycodeFacade::~PolycodeFacade() {}

  void PolycodeFacade::addEntity(Polycode::Entity *entity) {
    m_scene->addEntity(entity);
  }

  void PolycodeFacade::trackEntity(Polycode::Entity *entity) {
    m_scene->trackCollision(entity);
  }

  void PolycodeFacade::removeEntity(Polycode::Entity *entity) {
    m_scene->removeEntity(entity);
  }
}

