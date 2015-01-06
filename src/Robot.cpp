//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolyVector3.h"
#include "PolycodeFacade.hpp"
#include "Part.hpp"
#include "Robot.hpp"

using namespace Polycode;

namespace Synthetics {
  class IterateRobot : public IterateMethod {
    public:
      IterateRobot(Component *active, Part *activePart, Plug *activePlug, Polycode::Entity *plugShape) { 
        m_active = active;
        m_activePart = activePart;
        m_activePlug = activePlug;
        m_plugShape = plugShape; 
      }

      virtual ~IterateRobot() {}

      virtual void call(Compound *compound) {
        Component *component = dynamic_cast<Component *>(compound);
        if (component) {
          for (int i = 0; i < component->getNoParts(); i++) {
            Part *part = component->getPart(i);
            Plug *plug = part->getPlug(m_plugShape);
            if (plug) {
              if (m_activePlug) {
                m_activePlug->activate(false);
              }
              m_active = component;
              m_activePart = part;
              m_activePlug = plug;
              plug->activate(true);
            }
          }
        }
      }

      Component *getNewActiveComponent() {
        return m_active;
      }

      Part *getNewActivePart() {
        return m_activePart;
      }

      Plug *getNewActivePlug() {
        return m_activePlug;
      }

    private:
      Polycode::Entity *m_plugShape;
      Component *m_active;
      Part *m_activePart;
      Plug *m_activePlug;
  };

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

      Part *part = component->getPart(0);
      Plug *plug = part->getPlug(0);
      Vector3 rotation = m_activePlug->getFaceToFaceRotation(plug);
      part->getShape()->setRotationEuler(rotation);
      part->getShape()->setPosition(m_activePlug->getPosition());

      Robot::constructGraphic(m_polycodeFacade, m_activePart, component);
    }
    else {
      delete component;
    }
  }

  void Robot::remove() {
  }

  void Robot::activate(Polycode::Entity *plugShape) {
    IterateRobot *method = new IterateRobot(m_active, m_activePart, m_activePlug, plugShape);
    m_mother->iterate(method);
    m_active = method->getNewActiveComponent();
    m_activePart = method->getNewActivePart();
    m_activePlug = method->getNewActivePlug();
    delete method;
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

