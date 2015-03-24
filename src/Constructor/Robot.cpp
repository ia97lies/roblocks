//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolyVector3.h"
#include "PolycodeFacade.hpp"
#include "Part.hpp"
#include "Robot.hpp"

using namespace Polycode;

namespace Synthetics {
  namespace Constructor {

    //--------------------------------------------------------------------------
    class FindActivePlug : public IterateMethod {
      public:
        FindActivePlug(Component *active, Part *activePart, Plug *activePlug, Polycode::Entity *plugShape) { 
          m_activeComponent = active;
          m_activePart = activePart;
          m_activePlug = activePlug;
          m_plugShape = plugShape; 
        }

        virtual ~FindActivePlug() {}

        virtual void call(Compound *parent, Compound *compound) {
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

    //--------------------------------------------------------------------------
    class FindActiveInPlacePlug : public IterateMethod {
      public:
        FindActiveInPlacePlug(Part *activePart, Plug *activePlug, Polycode::Entity *plugShape) { 
          m_activePart = activePart;
          m_activePlug = activePlug;
          m_plugShape = plugShape; 
        }

        virtual ~FindActiveInPlacePlug() {}

        virtual void call(Compound *parent, Compound *compound) {
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

    //--------------------------------------------------------------------------
    class FindActiveKnob : public IterateMethod {
      public:
        FindActiveKnob(Polycode::Entity *knobShape) { 
          m_knobShape = knobShape; 
          m_activeKnob = NULL;
        }

        virtual ~FindActiveKnob() {}

        virtual void call(Compound *parent, Compound *compound) {
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

    //--------------------------------------------------------------------------
    Robot::Robot(PolycodeFacade *facade) {
      m_powerOn = false;
      m_polycodeFacade = facade;
      m_root = NULL;
      m_activeComponent = NULL;
      m_activePart = NULL;
      m_activePlug = NULL;
      m_activeKnob = NULL;
      m_inPlace = NULL;
      m_inPlacePart = NULL;
      m_inPlacePlug = NULL;
      m_curId = 1;
      m_components = new CompoundStore();
    }

    Robot::~Robot() {
      std::map<long, Compound*> map = m_components->getMap();
      std::map<long, Compound*>::iterator i;
      for (i = map.begin(); i != map.end(); i++) {
        Compound *compound = i->second;
        Component *component = dynamic_cast<Component *>(i->second);
        if (component) {
          Robot::destructGraphic(m_polycodeFacade, component);
        }
        delete compound;
        map.erase(i);
      }
    }

    void Robot::powerOn(bool on) {
      m_powerOn = on;
    }

    bool Robot::isPowerOn() {
      return m_powerOn;
    }

    void Robot::save(std::string file) {
    }

    void Robot::load(std::string file) {
    }

    void Robot::setRoot(Component *component) {
      if (m_root == NULL) {
        m_root = component;
        Compound::add(m_root);
        m_root->setId(0);
        m_components->insert(m_root);
        Robot::constructGraphic(m_polycodeFacade, NULL, component);
        for (int i = 0; i < component->getNoParts(); i++) {
          Robot::constructPlugsGraphic(m_polycodeFacade, component->getPart(i));
        }
      }
      else {
        delete component;
      }
    }

    void Robot::place(Component *component) {
      if (component && m_activeComponent != NULL && m_inPlace == NULL) {
        m_inPlace = component;
        m_inPlacePart = component->getPart(0);
        m_inPlacePlug = m_inPlacePart->getPlug(0);
        m_inPlacePlug->activate(true);
        Vector3 rotation = m_activePlug->getFaceToFaceRotation(m_inPlacePlug);
        m_inPlacePart->getShape()->setRotationEuler(rotation);
        m_inPlacePart->plug(m_activePart, 2);
        Robot::constructGraphic(m_polycodeFacade, m_activePart, component);
        Robot::constructPlugsGraphic(m_polycodeFacade, component->getPart(0));
        // Robot::setInPhysicsEnv(component)
        // hold it with a constraint
      }
      else {
        delete component;
      }
    }

    void Robot::add() {
      if (m_activeComponent != NULL && m_inPlace != NULL) {
        Component *component = m_inPlace;
        component->setId(m_curId++);
        m_components->insert(component);
        m_activeComponent->add(component);
        m_activePlug->setConnectedPlug(m_inPlacePlug);
        m_inPlacePlug->setConnectedPlug(m_activePlug);

        for (int i = 1; i < component->getNoParts(); i++) {
          Robot::constructPlugsGraphic(m_polycodeFacade, component->getPart(i));
        }

        // TODO: Wire: find all component/plugs which collide with our plugs
        //       and connect them, find component add us, find plugs point to us
        m_inPlacePart->plug(m_activePart, 0.5);

        // TODO: Simple:
        //       place a stiff hinge constraint between inplace and active part
        //       (use plugs for constraint coordinates)
        //       Complex:
        //       place a stiff hinge constraint to all sides (use plugs for
        //       collision and constraint coordinates)

        m_activePlug->activate(false);
        m_inPlacePlug->activate(false);
        m_activeComponent = NULL;
        m_activePart = NULL;
        m_activePlug = NULL;
        m_inPlace = NULL;
        m_inPlacePart = NULL;
        m_inPlacePlug = NULL;

        for (int i = 0; i < component->getNoParts(); i++) {
          for (int j = 0; j < component->getPart(i)->getNoPlugs(); j++) {
            if (component->getPart(i)->getPlug(j)->isActive()) {
              m_activeComponent = component;
              m_activePart = component->getPart(i);
              m_activePlug = component->getPart(i)->getPlug(j);
            }
          }
        }
      }
    }

    Component *Robot::remove() {
      Component *removedComponent = NULL;
      if (m_inPlace != NULL) {
        Robot::destructGraphic(m_polycodeFacade, m_inPlace);
        removedComponent = m_inPlace;
        m_inPlace = NULL;
        m_inPlacePart = NULL;
        m_inPlacePlug = NULL;
      }
      else if (m_activeComponent) {
        Plug *activePlug = NULL;
        Part *activePart = NULL;
        Component *activeComponent = NULL;
        // TODO an algorithme to detect wether it is possible to remove or not
        // * For more advanced removal, we need a island detection. If there are
        //   no parents which point directly or indirectly to the childs of the
        //   "removal" object, excluding the path over the "removal" object of
        //   course, then you MUST not remove the "removal" object else you can.
        //
        // Implement first bullet point, then think about the second one.
        if (m_activeComponent->getNoEntries() == 0) {
          std::vector<Compound *> parents =  m_root->getParents(m_activeComponent);
          for (int i = 0; i < parents.size(); i++) {
            parents.at(i)->remove(m_activeComponent);
            Component *component = dynamic_cast<Component *>(parents.at(i));
            if (component) {
              for (int j = 0; j < component->getNoParts(); j++) {
                Part *part = component->getPart(j);
                for (int k = 0; k < part->getNoPlugs(); k++) {
                  Plug *plug = part->getPlug(k);
                  if (plug->getConnectedPlug() && 
                      plug->getConnectedPlug()->getParent() == m_activeComponent) {
                    part->getPlug(k)->unsetConnectedPlug();
                    // TODO: Make an object out of this ugly part
                    activePlug = plug;
                    activePart = part;
                    activeComponent = component;
                    activePlug->activate(true);
                  }
                }
              }
            }
          }
        }
        Robot::destructGraphic(m_polycodeFacade, m_activeComponent);
        m_components->remove(m_activeComponent->getId());
        if (m_activeComponent == m_root) {
          m_root = NULL;
        }
        removedComponent = m_activeComponent;
        m_activeComponent = activeComponent;
        m_activePart = activePart;
        m_activePlug = activePlug;
      }
      return removedComponent;
    }

    void Robot::replace(Component *component) {
      if (m_inPlace != NULL) {
        Robot::destructGraphic(m_polycodeFacade, m_inPlace);
        delete m_inPlace;
        m_inPlace = NULL;
        m_inPlacePart = NULL;
        m_inPlacePlug = NULL;
        place(component);
      }
      else {
        delete component;
      }
    }

    void Robot::activate(Polycode::Entity *plugShape) {
      if (m_inPlace == NULL && m_root) {
        {
          FindActivePlug *method = new FindActivePlug(m_activeComponent, m_activePart, m_activePlug, plugShape);
          m_root->iterate(method);
          m_activeComponent = method->getNewActiveComponent();
          m_activePart = method->getNewActivePart();
          m_activePlug = method->getNewActivePlug();
          delete method;
        }

        {
          FindActiveKnob *method = new FindActiveKnob(plugShape);
          m_root->iterate(method);
          m_activeKnob = method->getActiveKnob();
          delete method;
        }

      }
      else if (m_inPlace) {
        {
          FindActiveInPlacePlug *method = new FindActiveInPlacePlug(m_inPlacePart, m_inPlacePlug, plugShape);
          m_inPlace->iterate(method);
          m_inPlacePart = method->getNewActivePart();
          m_inPlacePlug = method->getNewActivePlug();

          Vector3 rotation = m_activePlug->getFaceToFaceRotation(m_inPlacePlug);
          m_inPlacePart->getShape()->setRotationEuler(rotation);

          m_inPlacePart->plug(m_activePart, 2);
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
      return m_root == NULL;
    }

    Plug *Robot::getActivePlug() {
      return m_activePlug;
    }

    Knob *Robot::getActiveKnob() {
      return m_activeKnob;
    }

    Component *Robot::getInPlace() {
      return m_inPlace;
    }

    Component *Robot::getActiveComponent() {
      return m_activeComponent;
    }

    void Robot::update() {
      if (m_powerOn) {
        std::map<long, Compound*> map = m_components->getMap();
        std::map<long, Compound*>::iterator i;
        for (i = map.begin(); i != map.end(); i++) {
          Component *component = dynamic_cast<Component*>(i->second);
          if (component) {
            component->updateNg();
          }
        }
      }
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
        facade->trackCollisionEntity(curPlug->getShape());
        curPart->getShape()->addChild(curPlug->getShape());
        curPlug->getShape()->setRotationEuler(curPlug->getRotation());
        curPlug->getShape()->setPosition(curPlug->getPosition() * 0.5);
      }
    }

    void Robot::constructKnobGraphic(PolycodeFacade *facade, Part *curPart) {
      Knob *knob = curPart->getKnob();
      if (knob) {
        curPart->getShape()->addChild(knob->getShape());
        facade->trackCollisionEntity(knob->getShape());
      }
    }

    void Robot::destructGraphic(PolycodeFacade *facade, Component *component) {
      Part *parent = NULL;
      for (int i = 0; i < component->getNoParts(); i++) {
        Part *curPart = component->getPart(i);
        /* remove all childs of the shape */
        Entity *cur;
        while ((cur = curPart->getShape()->getChildAtIndex(0)) != NULL) {
          curPart->getShape()->removeChild(cur);
        }

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
            curPart->getShape()->removeChild(knob->getShape());
            facade->removeEntity(knob->getShape());
          }
        }
      }
    }
  }
}
