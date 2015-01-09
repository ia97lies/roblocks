//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolyVector3.h"
#include "PolycodeFacade.hpp"
#include "Part.hpp"
#include "Robot.hpp"

using namespace Polycode;

namespace Synthetics {
  class FindActivePlug : public IterateMethod {
    public:
      FindActivePlug(Component *active, Part *activePart, Plug *activePlug, Polycode::Entity *plugShape) { 
        m_activeComponent = active;
        m_activePart = activePart;
        m_activePlug = activePlug;
        m_plugShape = plugShape; 
      }

      virtual ~FindActivePlug() {}

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
              m_activeComponent = component;
              m_activePart = part;
              m_activePlug = plug;
              plug->activate(true);
            }
          }
        }
      }

      Component *getNewActiveComponent() {
        return m_activeComponent;
      }

      Part *getNewActivePart() {
        return m_activePart;
      }

      Plug *getNewActivePlug() {
        return m_activePlug;
      }

    private:
      Polycode::Entity *m_plugShape;
      Component *m_activeComponent;
      Part *m_activePart;
      Plug *m_activePlug;
  };

  class FindActiveParkPlug : public IterateMethod {
    public:
      FindActiveParkPlug(Part *activePart, Plug *activePlug, Polycode::Entity *plugShape) { 
        m_activePart = activePart;
        m_activePlug = activePlug;
        m_plugShape = plugShape; 
      }

      virtual ~FindActiveParkPlug() {}

      virtual void call(Compound *compound) {
        Component *component = dynamic_cast<Component *>(compound);
        if (component) {
          Part *part = component->getPart(0);
          Plug *plug = part->getPlug(m_plugShape);
          if (plug) {
            if (m_activePlug) {
              m_activePlug->activate(false);
            }
            m_activePart = part;
            m_activePlug = plug;
            plug->activate(true);
          }
        }
      }

      Part *getNewActivePart() {
        return m_activePart;
      }

      Plug *getNewActivePlug() {
        return m_activePlug;
      }

    private:
      Polycode::Entity *m_plugShape;
      Part *m_activePart;
      Plug *m_activePlug;
  };

  class FindParents : public IterateMethod {
    public:
      FindParents(Component *active) { 
        m_activeComponent = active;
      }

      virtual ~FindParents() {}

      virtual void call(Compound *compound) {
        Component *component = dynamic_cast<Component *>(compound);
        if (component ) {
        }
      }

    private:
      Component *m_activeComponent;
  };

  Robot::Robot(PolycodeFacade *facade) {
    m_polycodeFacade = facade;
    m_mother = NULL;
    m_activeComponent = NULL;
    m_activePart = NULL;
    m_activePlug = NULL;
    m_inPlace = NULL;
    m_inPlacePart = NULL;
    m_inPlacePlug = NULL;
    m_rotation = Vector3(0,0,0);
  }

  Robot::~Robot() {
  }

  void Robot::place(Component *component) {
    if (m_activeComponent != NULL && m_inPlace == NULL) {
      m_inPlace = component;
      m_inPlacePart = component->getPart(0);
      m_inPlacePlug = m_inPlacePart->getPlug(0);
      m_inPlacePlug->activate(true);
      m_rotation = m_activePlug->getFaceToFaceRotation(m_inPlacePlug);
      m_inPlacePart->getShape()->setRotationEuler(m_rotation);
      m_inPlacePart->getShape()->setPosition(m_activePlug->getPosition()*2);
      Robot::constructGraphic(m_polycodeFacade, m_activePart, component);
    }
    else {
      delete component;
    }
  }

  void Robot::add(Component *component) {
    if (m_mother == NULL) {
      m_mother = component;
      Robot::constructGraphic(m_polycodeFacade, NULL, component);
    }
    else {
      delete component;
    }
  }

  void Robot::add() {
    if (m_activeComponent != NULL && m_inPlace != NULL) {
      Component *component = m_inPlace;
      m_activeComponent->add(component);

      Part *part = component->getPart(0);
      Plug *plug = part->getPlug(0);
      part->getShape()->setRotationEuler(m_rotation);
      part->getShape()->setPosition(m_activePlug->getPosition());

      m_activePlug->activate(false);
      m_inPlacePlug->activate(false);
      m_activeComponent = NULL;
      m_activePart = NULL;
      m_activePlug = NULL;
      m_inPlace = NULL;
      m_inPlacePart = NULL;
      m_inPlacePlug = NULL;
    }
  }

  void Robot::remove() {

  }

  void Robot::activate(Polycode::Entity *plugShape) {
    if (m_inPlace == NULL) {
      FindActivePlug *method = new FindActivePlug(m_activeComponent, m_activePart, m_activePlug, plugShape);
      m_mother->iterate(method);
      m_activeComponent = method->getNewActiveComponent();
      m_activePart = method->getNewActivePart();
      m_activePlug = method->getNewActivePlug();
      delete method;
    }
    else {
      FindActiveParkPlug *method = new FindActiveParkPlug(m_inPlacePart, m_inPlacePlug, plugShape);
      m_inPlace->iterate(method);
      m_inPlacePart = method->getNewActivePart();
      m_inPlacePlug = method->getNewActivePlug();

      m_rotation = m_activePlug->getFaceToFaceRotation(m_inPlacePlug);
      m_inPlacePart->getShape()->setRotationEuler(m_rotation);
      m_inPlacePart->getShape()->setPosition(m_activePlug->getPosition()*2);

      delete method;
    }
  }

  void Robot::rotateInPlace() {
    if (m_inPlace != NULL) {
      Vector3 rotate = m_inPlacePlug->getPosition() * 90;
      m_rotation += rotate;
      if (m_rotation.x >= 360) m_rotation.x = 0;
      if (m_rotation.y >= 360) m_rotation.y = 0;
      if (m_rotation.z >= 360) m_rotation.z = 0;
      m_inPlacePart->getShape()->setRotationEuler(m_rotation);
    }
  }

  bool Robot::isEmpty() {
    return m_mother == NULL;
  }

  bool Robot::inPlace() {
    return m_inPlace != NULL;
  }

  Plug *Robot::getActivePlug() {
      return m_activePlug;
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

