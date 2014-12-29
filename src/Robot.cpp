//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolyVector3.h"
#include "PolycodeFacade.hpp"
#include "Part.hpp"
#include "Robot.hpp"

using namespace Polycode;

namespace Synthetics {
  Robot::Robot(PolycodeFacade *facade) {
    m_polycodeFacade = facade;
    m_mother = NULL;
    m_active = NULL;
    m_activePlug = NULL;
  }

  Robot::~Robot() {
  }

  void Robot::add(Component *component) {
    if (m_mother == NULL) {
      m_mother = component;
      constructGraphic(NULL, component);
    }
    else if (m_active != NULL) {
      // TODO: set correct position and rotation of the added component
      // TODO: store as well the active plug for calculation of position and rotation
      m_active->add(component);
      constructGraphic(NULL, component);
    }
    else {
      delete component;
    }
  }

  void Robot::remove() {
  }

  void Robot::activate(Polycode::Entity *plugShape) {
    Component *curComponent = m_mother;
    Component *active = NULL;
    while (curComponent && !active) {
      for (int i = 0; i < curComponent->getNoParts(); i++) {
        Part *curPart = curComponent->getPart(i);
        Plug *plug = curPart->getPlug(plugShape);
        if (plug) {
          plug->activate(true);
          if (m_activePlug) {
            m_activePlug->activate(false);
          }
          m_activePlug = plug;
          m_active = active = curComponent;
        }
      }
      // TODO: iterate over components
      curComponent = NULL;
    }
  }

  void Robot::constructGraphic(Part *parent, Component *component) {
    for (int i = 0; i < component->getNoParts(); i++) {
      Part *curPart = component->getPart(i);
      if (parent == NULL) {
        m_polycodeFacade->addEntity(curPart->getShape());
      }
      else {
        parent->getShape()->addChild(curPart->getShape());
      }
      parent = curPart;
      for (int j = 0; j < curPart->getNoPlugs(); j++) {
        Plug *curPlug = curPart->getPlug(j);
        curPart->getShape()->addChild(curPlug->getShape());
        m_polycodeFacade->trackEntity(curPlug->getShape());
        curPlug->getShape()->setRotationEuler(curPlug->getRotation());
        curPlug->getShape()->setPosition(curPlug->getPosition());

      }
    }
  }
}

