//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolyString.h"
#include "PolyUITreeEvent.h"

#include "PolycodeFacade.hpp"
#include "Part.hpp"
#include "OrbitCamera.hpp"
#include "Robot.hpp"
#include "Display.hpp"
#include "ContextMenu.hpp"

#include "CommandSetRoot.hpp"
#include "CommandActivate.hpp"
#include "CommandPlace.hpp"
#include "CommandRotateInPlace.hpp"
#include "CommandAdd.hpp"
#include "CommandRemove.hpp"


using namespace Polycode;

namespace Synthetics {
  namespace Constructor {
    class ChangeInPlace : public ChangeSelection {
      public:
        ChangeInPlace(Core *core, PhysicsScene *scene, Components::Factory *factory, Robot *robot) {
          m_core = core;
          m_scene = scene;
          m_factory = factory;
          m_robot = robot;
        }
        virtual ~ChangeInPlace() {}
        virtual void onChange(std::string name) {
          if (m_robot->getInPlace()) {
            Component *component = m_factory->createComponent(name, m_scene);
            m_robot->replace(component);
          }
        }
      private:
        Core *m_core;
        PhysicsScene *m_scene;
        Components::Factory *m_factory;
        Robot *m_robot;
    };

    Display::Display(Core *core, Configurator *conf, Components::Factory *factory) {
      m_core = core;
      m_conf = conf;
      m_factory = factory;
      m_scene = new PhysicsScene();
      m_camera = new OrbitCamera(m_core, m_scene);
      m_camera->activate(true);

      m_on = false;
      activate();

      m_robot = new Robot(new PolycodeFacade(m_core, m_scene));

      m_camera->update();

      m_selectorDisplay = new SelectorDisplay(m_core, m_conf, m_factory, new ChangeInPlace(m_core, m_scene, m_factory, m_robot));


      m_history = new History(m_conf->getHistory());
      ContextMenu *menu = new ContextMenu(m_core, m_conf);
    }

    Display::~Display() {
    }

    void Display::handleEvent(Event *e) {
      if(e->getDispatcher() == m_core->getInput()) {
        InputEvent *inputEvent = (InputEvent*)e;

        switch(e->getEventCode()) {
          case InputEvent::EVENT_KEYDOWN:
            switch (inputEvent->keyCode()) {
              case KEY_DELETE:
                if (m_robot) {
                  Command *command = new CommandRemove(m_robot);
                  m_history->execute(command);
                }
                break;
              case KEY_RETURN:
                {
                  place();
                }
                break;
              case KEY_UP:
                {
                  Command *command = new CommandRotateInPlace(m_robot, 1);
                  m_history->execute(command);
                }
                break;
              case KEY_DOWN:
                {
                  Command *command = new CommandRotateInPlace(m_robot, -1);
                  m_history->execute(command);
                }
                break;
              case KEY_o:
                {
                  m_robot->powerOn(!m_robot->isPowerOn());
                }
                break;
              case KEY_u:
                {
                  m_history->undo();
                }
                break;
              case KEY_r:
                {
                  m_history->redo();
                }
                break;
            }
            break;
          case InputEvent::EVENT_MOUSEDOWN:
            switch(inputEvent->getMouseButton()) {
              case CoreInput::MOUSE_BUTTON1:
                {
                  Ray ray = m_scene->projectRayFromCameraAndViewportCoordinate(m_scene->getActiveCamera(), inputEvent->mousePosition);
                  RayTestResult res = m_scene->getFirstEntityInRay(ray.origin, ray.direction * 300.0);
                  if(res.entity) {
                    Command *command = new CommandActivate(m_robot, res.entity);
                    m_history->execute(command);
                  }
                  if (m_robot->getActiveKnob()) {
                    m_camera->activate(false);
                  }
                }
                break;
              case CoreInput::MOUSE_BUTTON2:
                {
                  /* TODO make context menu visible */
                }
                break;
            }
            break;
          case InputEvent::EVENT_MOUSEUP:
            switch(inputEvent->getMouseButton()) {
              case CoreInput::MOUSE_BUTTON1:
                {
                  if (m_robot->getActiveKnob()) {
                    m_robot->deactivate(m_robot->getActiveKnob()->getShape());
                    m_camera->activate(true);
                  }
                }
                break;
                case CoreInput::MOUSE_BUTTON2:
                {
                  /* TODO make context menu invisible and execute active menu entry if any */
                  /*
                  Vector2 mouse = core->getInput()->getMousePosition();
                  Ray ray = scene->projectRayFromCameraAndViewportCoordinate(scene->getActiveCamera(), mouse);

                  SceneEntity * entity = scene->getEntityAtPosition(ray.origin.x, ray.origin.y);
                  */
                }
                break;

            }
            break;
          case InputEvent::EVENT_MOUSEMOVE:
            {
              Vector3 delta(m_core->getInput()->getMouseDelta().x, m_core->getInput()->getMouseDelta().y, 0);
              m_robot->mouseMove(delta);
            }
            break;
        }
      }
    }

    void Display::update(Number dt) {
      m_robot->update(dt);
    }

    void Display::activate() {
      if (!m_on) {
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEUP);
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_DOUBLECLICK);
        m_on = true;
      }
    }

    void Display::deactivate() {
      if (m_on) {
        m_core->getInput()->removeAllHandlersForListener(this);
        m_on = false;
      }
    }

    void Display::place() {
      if (m_robot->isEmpty()) {
        Component *component = m_factory->createComponent(m_selectorDisplay->getText(), m_scene);
        Command *command = new CommandSetRoot(m_robot, component);
        m_history->execute(command);
      }
      else if (!m_robot->getInPlace()) {
        Component *component = m_factory->createComponent(m_selectorDisplay->getText(), m_scene);
        Command *command = new CommandPlace(m_robot, component);
        m_history->execute(command);
      }
      else {
        Component *component = m_robot->getInPlace();
        Command *command = new CommandAdd(m_robot, component);
        m_history->execute(command);
      }
    }
  }
}

