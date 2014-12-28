//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolyVector3.h"
#include "Part.hpp"
#include "Robot.hpp"

using namespace Polycode;

namespace Synthetics {
  Robot::Robot(Core *core, CollisionScene *scene) {
    m_core = core;
    m_scene = scene;
    m_mother = new Entity();
  }

  Robot::~Robot() {
  }

  void Robot::add(Component *component) {
    for (int i = 0; i < component->getNoParts(); i++) {
      Part *curPart = component->getPart(i);
      m_scene->addEntity(curPart->getShape());
      for (int j = 0; j < curPart->getNoPlugs(); j++) {
        Plug *curPlug = curPart->getPlug(j);
        curPart->getShape()->addChild(curPlug->getShape());
        m_scene->trackCollision(curPlug->getShape());
        curPlug->getShape()->setRotationEuler(curPlug->getRotation());
        curPlug->getShape()->setPosition(curPlug->getPosition());

      }
    }
  }

  void Robot::remove() {
  }

  void Robot::activate(void *plug) {
  }
}

