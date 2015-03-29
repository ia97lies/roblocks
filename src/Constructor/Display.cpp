//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolyString.h"
#include "PolyUITreeEvent.h"

#include "PolycodeFacade.hpp"
#include "Part.hpp"
#include "OrbitCamera.hpp"
#include "Robot.hpp"
#include "FileManager.hpp"
#include "Display.hpp"

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

    class DoneCompletion : public FileManagerCompletion {
      public:
        DoneCompletion(Display *constructor, MovingCamera *camera) {
          m_constructor = constructor;
          m_camera = camera;
        }
        virtual ~DoneCompletion() {}
        virtual void done() {
          m_constructor->activate(true);
          m_camera->activate(true);
        }
      private:
        Display *m_constructor;
        MovingCamera *m_camera;
    };

    Display::Display(Core *core, Configurator *conf, Components::Factory *factory) : EventHandler() {
      m_core = core;
      m_conf = conf;
      m_factory = factory;
      m_scene = new PhysicsScene();
      m_camera = new OrbitCamera(m_core, m_scene);
      m_camera->activate(true);
      m_lastClickTime = 0;

      m_on = false;
      activate(true);

      m_robot = new Robot(new PolycodeFacade(m_core, m_scene));

      m_camera->update();

      m_selectorDisplay = new SelectorDisplay(m_core, m_conf, m_factory, new ChangeInPlace(m_core, m_scene, m_factory, m_robot));


      Scene *scene = new Scene(Scene::SCENE_2D_TOPLEFT);
      scene->doVisibilityChecking(false);
      scene->getDefaultCamera()->frustumCulling = false;
      scene->rootEntity.processInputEvents = true;

      std::vector<String> extensions;
      extensions.push_back("*.lua");
      m_fileDialog = new FileManager(m_core, m_scene, m_factory, extensions);
      scene->addEntity(m_fileDialog);
      
      m_history = new History(m_conf->getHistory());
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
                // delete active component
                if (m_robot) {
                  Command *command = new CommandRemove(m_robot, m_core, m_scene);
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
              case KEY_s:
                {
                  DoneCompletion *completion = new DoneCompletion(this, m_camera);
                  activate(false);
                  m_camera->activate(false);
                  m_fileDialog->save(m_robot, completion);
                }
                break;
              case KEY_l:
                {
                  delete m_robot;
                  m_robot = new Robot(new PolycodeFacade(m_core, m_scene));
                  DoneCompletion *completion = new DoneCompletion(this, m_camera);
                  activate(false);
                  m_camera->activate(false);
                  m_fileDialog->load(m_robot, completion);
                }
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
                  // double click, somehow InputEvent::EVENT_DOUBLECLICK won't work, do it by my self
                  unsigned int timestamp = m_core->getTicks();
                  if (timestamp - m_lastClickTime < 200) {
                    place();
                  }
                  m_lastClickTime = m_core->getTicks();
                }
                break;
            }
            break;
          case InputEvent::EVENT_MOUSEUP:
            switch(inputEvent->getMouseButton()) {
              case CoreInput::MOUSE_BUTTON1:
                {
                  m_robot->deactivate();
                  m_camera->activate(true);
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
            break;
        }
      }
    }

    void Display::update() {
      m_fileDialog->Update();
      m_robot->update();
    }

    void Display::activate(bool on) {
      if (on && !m_on) {
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEUP);
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_DOUBLECLICK);
        m_core->getInput()->addEventListener(this, UIEvent::OK_EVENT);
        m_core->getInput()->addEventListener(this, UIEvent::CANCEL_EVENT);
      }
      else if (!on && m_on) {
        m_core->getInput()->removeEventListener(this, InputEvent::EVENT_KEYDOWN);
        m_core->getInput()->removeEventListener(this, InputEvent::EVENT_MOUSEDOWN);
        m_core->getInput()->removeEventListener(this, InputEvent::EVENT_MOUSEUP);
        m_core->getInput()->removeEventListener(this, InputEvent::EVENT_MOUSEMOVE);
        m_core->getInput()->removeEventListener(this, InputEvent::EVENT_DOUBLECLICK);
        m_core->getInput()->addEventListener(this, UIEvent::OK_EVENT);
        m_core->getInput()->addEventListener(this, UIEvent::CANCEL_EVENT);
      }
      m_on = on;
    }

    void Display::place() {
      // add current selected component to current active component
      if (m_robot->isEmpty()) {
        Component *component = m_factory->createComponent(m_selectorDisplay->getText(), m_scene);
        Command *command = new CommandSetRoot(m_robot, component, m_core, m_scene);
        m_history->execute(command);
      }
      else if (!m_robot->getInPlace()) {
        Component *component = m_factory->createComponent(m_selectorDisplay->getText(), m_scene);
        Command *command = new CommandPlace(m_robot, component, m_core, m_scene);
        m_history->execute(command);
      }
      else {
        Component *component = m_robot->getInPlace();
        Command *command = new CommandAdd(m_robot, component, m_core, m_scene);
        m_history->execute(command);
      }
    }
  }
}

