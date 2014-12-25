//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolyVector3.h"
#include "Part.hpp"
#include "Robot.hpp"

namespace Synthetics {
  Robot::Robot(Polycode::Core *core, Polycode::CollisionScene *scene) {
    m_core = core;
    m_scene = scene;
  }

  Robot::~Robot() {
  }

  void Robot::add(Component *component) {
    for (int i = 0; i < component->getNoParts(); i++) {
      Part *cur = component->getPart(i);
      m_scene->addEntity(cur->getShape());
    }
  }

  void Robot::remove() {
  }

  void Robot::activate(void *plug) {
  }
}

