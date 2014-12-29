//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolyVector3.h"
#include "Part.hpp"
#include "Robot.hpp"

using namespace Polycode;

namespace Synthetics {
  Robot::Robot(CollisionScene *scene) {
    m_scene = scene;
    m_mother = NULL;
    m_active = NULL;
  }

  Robot::~Robot() {
  }

  void Robot::add(Component *component) {
    Part *parent = NULL;
    for (int i = 0; i < component->getNoParts(); i++) {
      Part *curPart = component->getPart(i);
      if (parent == NULL) {
        m_scene->addEntity(curPart->getShape());
      }
      else {
        parent->getShape()->addChild(curPart->getShape());
      }
      parent = curPart;
      for (int j = 0; j < curPart->getNoPlugs(); j++) {
        Plug *curPlug = curPart->getPlug(j);
        curPart->getShape()->addChild(curPlug->getShape());
        m_scene->trackCollision(curPlug->getShape());
        curPlug->getShape()->setRotationEuler(curPlug->getRotation());
        curPlug->getShape()->setPosition(curPlug->getPosition());

      }
    }
    if (m_mother == NULL) {
      m_mother = component;
    }
    else if (m_active != NULL) {
      m_active->add(component);
    }
  }

  void Robot::remove() {
  }

  void Robot::activate(void *plug) {
    Component *curComponent = m_mother;
    while (curComponent && !m_active) {
      for (int i = 0; i < curComponent->getNoParts(); i++) {
      }
    }
  }
}

