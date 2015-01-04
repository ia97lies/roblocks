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
      Robot::constructGraphic(m_polycodeFacade, NULL, component);
    }
    else if (m_active != NULL) {
      m_active->add(component);

      // TODO: get active part/plug from added component
      Part *part = component->getPart(0);
      Plug *plug = part->getPlug(0);
      Vector3 rotation = m_activePlug->getFaceToFaceRotation(plug);
      fprintf(stderr, "Rotation: %f, %f, %f\n", rotation.x, rotation.y, rotation.z);
      // TODO: set correct position and rotation of the added component
      part->getShape()->setRotationEuler(rotation);
      part->getShape()->setPosition(m_activePlug->getPosition());

      fprintf(stderr, "Position: %f, %f, %f\n", m_activePlug->getPosition().x, m_activePlug->getPosition().y, m_activePlug->getPosition().z);

      Robot::constructGraphic(m_polycodeFacade, m_activePart, component);
    }
    else {
      delete component;
    }
  }

  void Robot::remove() {
  }

  void Robot::activate(Polycode::Entity *plugShape) {
    activate(m_mother, plugShape);
    fprintf(stderr, "XXX: %d\n", m_mother->getNoEntries());
    for (int i = 0; i < m_mother->getNoEntries(); i++) {
      fprintf(stderr, "XXX: %d\n", i);
      activate(dynamic_cast<Component *>(m_mother->get(i)), plugShape);
    }
  }

  void Robot::activate(Component *component, Polycode::Entity *plugShape) {
    Component *active = NULL;
    for (int i = 0; i < component->getNoParts(); i++) {
      Part *curPart = component->getPart(i);
      Plug *plug = curPart->getPlug(plugShape);
      if (plug) {
        plug->activate(true);
        if (m_activePlug) {
          m_activePlug->activate(false);
        }
        m_activePlug = plug;
        m_activePart = curPart;
        m_active = active = component;
      }
    }
  }

  Plug *Robot::getActivePlug() {
    return m_activePlug;
  }

  bool Robot::isEmpty() {
    return m_mother == NULL;
  }

  void Robot::constructGraphic(PolycodeFacade *facade, Part *parent, Component *component) {
    for (int i = 0; i < component->getNoParts(); i++) {
      Part *curPart = component->getPart(i);
      if (parent == NULL) {
        facade->addEntity(curPart->getShape());
      }
      else {
        parent->getShape()->addChild(curPart->getShape());
      }
      parent = curPart;
      for (int j = 0; j < curPart->getNoPlugs(); j++) {
        Plug *curPlug = curPart->getPlug(j);
        facade->trackEntity(curPlug->getShape());
        curPart->getShape()->addChild(curPlug->getShape());
        curPlug->getShape()->setRotationEuler(curPlug->getRotation());
        curPlug->getShape()->setPosition(curPlug->getPosition() * 0.5);
      }
    }
  }

  void Robot::destructGraphic(PolycodeFacade *facade, Part *parent, Component *component) {
    for (int i = 0; i < component->getNoParts(); i++) {
      Part *curPart = component->getPart(i);
      if (parent == NULL) {
        facade->removeEntity(curPart->getShape());
      }
      else {
        parent->getShape()->removeChild(curPart->getShape());
      }
      parent = curPart;
      for (int j = 0; j < curPart->getNoPlugs(); j++) {
        Plug *curPlug = curPart->getPlug(j);
        curPart->getShape()->removeChild(curPlug->getShape());
        facade->removeEntity(curPlug->getShape());
      }
    }
  }

}

