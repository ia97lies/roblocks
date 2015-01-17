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

  class FindActiveInPlacePlug : public IterateMethod {
    public:
      FindActiveInPlacePlug(Part *activePart, Plug *activePlug, Polycode::Entity *plugShape) { 
        m_activePart = activePart;
        m_activePlug = activePlug;
        m_plugShape = plugShape; 
      }

      virtual ~FindActiveInPlacePlug() {}

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

  class FindActiveKnob : public IterateMethod {
    public:
      FindActiveKnob(Polycode::Entity *knobShape) { 
        m_knobShape = knobShape; 
        m_activeKnob = NULL;
      }

      virtual ~FindActiveKnob() {}

      virtual void call(Compound *compound) {
        Component *component = dynamic_cast<Component *>(compound);
        if (component) {
          for (int i = 0; i < component->getNoParts(); i++) {
            Part *part = component->getPart(i);
            Knob *knob = part->getKnob();
            if (knob && knob->getShape() == m_knobShape) {
              knob->activate(true);
              m_activeKnob = knob;
            }
          }
        }
      }

      Knob *getActiveKnob() {
        return m_activeKnob;
      }

    private:
      Polycode::Entity *m_knobShape;
      Knob *m_activeKnob;
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
    m_activeKnob = NULL;
    m_inPlace = NULL;
    m_inPlacePart = NULL;
    m_inPlacePlug = NULL;
  }

  Robot::~Robot() {
  }

  void Robot::place(Component *component) {
    if (m_activeComponent != NULL && m_inPlace == NULL) {
      m_inPlace = component;
      m_inPlacePart = component->getPart(0);
      m_inPlacePlug = m_inPlacePart->getPlug(0);
      m_inPlacePlug->activate(true);
      Vector3 rotation = m_activePlug->getFaceToFaceRotation(m_inPlacePlug);
      m_inPlacePart->getShape()->setRotationEuler(rotation);
      m_inPlacePart->plug(m_activePlug, m_inPlacePlug, 2);
      Robot::constructGraphic(m_polycodeFacade, m_activePart, component);
      Robot::constructPlugsGraphic(m_polycodeFacade, component->getPart(0));
    }
    else {
      delete component;
    }
  }

  void Robot::add(Component *component) {
    if (m_mother == NULL) {
      m_mother = component;
      Robot::constructGraphic(m_polycodeFacade, NULL, component);
      for (int i = 0; i < component->getNoParts(); i++) {
        Robot::constructPlugsGraphic(m_polycodeFacade, component->getPart(i));
      }
    }
    else {
      delete component;
    }
  }

  void Robot::add() {
    if (m_activeComponent != NULL && m_inPlace != NULL) {
      Component *component = m_inPlace;
      m_activeComponent->add(component);

      for (int i = 1; i < component->getNoParts(); i++) {
        Robot::constructPlugsGraphic(m_polycodeFacade, component->getPart(i));
      }

      m_inPlacePart->plug(m_activePlug, m_inPlacePlug, 0.5);

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
    if (m_inPlace != NULL) {
      Robot::destructGraphic(m_polycodeFacade, m_inPlace);
      delete m_inPlace;
      m_inPlace = NULL;
      m_inPlacePart = NULL;
      m_inPlacePlug = NULL;
    }
    else if (m_activeComponent) {
      // TODO an algorithme to detect wether it is possible to remove or not
      // * First shot whould be remove only elements with no childs. But if we 
      //   also support thigt connection it is most likely that there are no 
      //   removable elements with this approache. But as a first solution this
      //   is feasable.
      // * For more advanced removal, we need a island detection. If there are
      //   no parents which point directly or indirectly to the childs of the
      //   "removal" object, excluding the path over the "removal" object of
      //   course, then you MUST not remove the "removal" object else you can.
      //
      // Implement first bullet point, then think about the second one.
      if (m_activeComponent->getNoEntries() == 0) {
        std::vector<Compound *> parents =  m_mother->getParents(m_activeComponent);
        for (int i = 0; i < parents.size(); i++) {
          parents.at(i)->remove(m_activeComponent);
        }
        Robot::destructGraphic(m_polycodeFacade, m_activeComponent);
      }
    }
  }

  void Robot::activate(Polycode::Entity *plugShape) {
    if (m_inPlace == NULL) {
      {
        FindActivePlug *method = new FindActivePlug(m_activeComponent, m_activePart, m_activePlug, plugShape);
        m_mother->iterate(method);
        m_activeComponent = method->getNewActiveComponent();
        m_activePart = method->getNewActivePart();
        m_activePlug = method->getNewActivePlug();
        delete method;
      }

      {
        FindActiveKnob *method = new FindActiveKnob(plugShape);
        m_mother->iterate(method);
        m_activeKnob = method->getActiveKnob();
        delete method;
      }

    }
    else {
      {
        FindActiveInPlacePlug *method = new FindActiveInPlacePlug(m_inPlacePart, m_inPlacePlug, plugShape);
        m_inPlace->iterate(method);
        m_inPlacePart = method->getNewActivePart();
        m_inPlacePlug = method->getNewActivePlug();

        Vector3 rotation = m_activePlug->getFaceToFaceRotation(m_inPlacePlug);
        m_inPlacePart->getShape()->setRotationEuler(rotation);

        m_inPlacePart->plug(m_activePlug, m_inPlacePlug, 2);
        delete method;
      }
    }
  }

  void Robot::deactivate() {
    if (m_activeKnob) {
      m_activeKnob->activate(false);
    }
    m_activeKnob = NULL;
  }

  void Robot::rotateInPlace(int direction) {
    int one = direction/direction;
    if (m_inPlace != NULL) {
      Vector3 position = m_inPlacePlug->getPosition();
      position.Normalize();
      Vector3 rotate = position * 90 * direction;
      Vector3 rotation = m_inPlacePart->getShape()->getRotationEuler();
      m_inPlacePart->getShape()->Pitch(rotate.x);
      m_inPlacePart->getShape()->Yaw(rotate.y);
      m_inPlacePart->getShape()->Roll(rotate.z);
    }
  }

  void Robot::mouseMove(Vector3 delta) {
    if (m_activeKnob) {
      m_activeKnob->handleInput(delta);
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

  Knob *Robot::getActiveKnob() {
      return m_activeKnob;
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
      Robot::constructKnobGraphic(facade, curPart);
    }
  }

  void Robot::constructPlugsGraphic(PolycodeFacade *facade, Part *curPart) {
    for (int j = 0; j < curPart->getNoPlugs(); j++) {
      Plug *curPlug = curPart->getPlug(j);
      facade->trackEntity(curPlug->getShape());
      curPart->getShape()->addChild(curPlug->getShape());
      curPlug->getShape()->setRotationEuler(curPlug->getRotation());
      curPlug->getShape()->setPosition(curPlug->getPosition() * 0.5);
    }
  }

  void Robot::constructKnobGraphic(PolycodeFacade *facade, Part *curPart) {
    Knob *knob = curPart->getKnob();
    if (knob) {
      facade->trackEntity(knob->getShape());
    }
  }

  void Robot::destructGraphic(PolycodeFacade *facade, Component *component) {
    Part *parent = NULL;
    for (int i = 0; i < component->getNoParts(); i++) {
      Part *curPart = component->getPart(i);
      if (parent == NULL) {
        Polycode::Entity *parentEntity = curPart->getShape()->getParentEntity();
        if (parentEntity) {
          parentEntity->removeChild(curPart->getShape());
        }
        else {
          facade->removeEntity(curPart->getShape());
        }
      }
      else {
        parent->getShape()->removeChild(curPart->getShape());
      }
      parent = curPart;
      for (int j = 0; j < curPart->getNoPlugs(); j++) {
        Plug *curPlug = curPart->getPlug(j);
        curPart->getShape()->removeChild(curPlug->getShape());
        facade->removeEntity(curPlug->getShape());

        Knob *knob = curPart->getKnob();
        if (knob) {
          facade->removeEntity(knob->getShape());
        }
      }
    }
  }

}
