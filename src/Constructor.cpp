//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolyString.h"
#include "PolyUIFileDialog.h"
#include "PolycodeFacade.hpp"
#include "Part.hpp"
#include "OrbitCamera.hpp"
#include "Robot.hpp"
#include "Constructor.hpp"

using namespace Polycode;

namespace Synthetics {

  Constructor::Constructor(Core *core, Configurator *conf, Components::Factory *factory) : EventHandler() {
    m_core = core;
    m_conf = conf;
    m_factory = factory;
    m_scene = new CollisionScene();
    m_camera = new OrbitCamera(m_core, m_scene);
    m_camera->activate(true);

    m_core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
    m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
    m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEUP);
    m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);

    m_mother = new Robot(new PolycodeFacade(m_core, m_scene));

    m_camera->update();

    m_selectorDisplay = new SelectorDisplay(m_core, m_conf, m_factory);
  }

  Constructor::~Constructor() {
  }

  void Constructor::handleEvent(Event *e) {
    if(e->getDispatcher() == m_core->getInput()) {
      InputEvent *inputEvent = (InputEvent*)e;

      switch(e->getEventCode()) {
        case InputEvent::EVENT_KEYDOWN:
          switch (inputEvent->keyCode()) {
            case KEY_DELETE:
              // delete active component
              if (m_mother) {
                m_mother->remove();
              }
              break;
            case KEY_RETURN:
              // add current selected component to current active component
              if (m_mother->isEmpty()) {
                Component *component = m_factory->createComponent(m_selectorDisplay->getText(), m_core, m_scene);
                m_mother->add(component);
              }
              else if (!m_mother->inPlace()) {
                Component *component = m_factory->createComponent(m_selectorDisplay->getText(), m_core, m_scene);
                m_mother->place(component);
              }
              else {
                m_mother->add();
              }
              break;
            case KEY_UP:
              m_mother->rotateInPlace(1);
              break;
            case KEY_DOWN:
              m_mother->rotateInPlace(-1);
              break;
            case KEY_o:
              m_mother->powerOn(!m_mother->isPowerOn());
              break;
            case KEY_l:
              // start file selection menu
              //std::vector<String> extensions;
              //extensions.push_back("lua");
              //UIFileDialog *dialog = new UIFileDialog(String("."), false, extensions, false);
              open();
              setCPath("./lib/?.so");
              lua_pushlightuserdata(m_L, m_factory);
              lua_setfield(m_L, LUA_REGISTRYINDEX, "factory");

              if (luaL_loadfile(m_L, ".snapshot.lua") || lua_pcall(m_L, 0, 0, 0)) {
                error("cannot load .snapshot.lua: %s\n", lua_tostring(m_L, -1));
              }
              close();

              break;
          }
          break;
        case InputEvent::EVENT_MOUSEDOWN:
          switch(inputEvent->getMouseButton()) {
            case CoreInput::MOUSE_BUTTON1:
              Ray ray = m_scene->projectRayFromCameraAndViewportCoordinate(m_scene->getActiveCamera(), inputEvent->mousePosition);
              RayTestResult res = m_scene->getFirstEntityInRay(ray.origin, ray.direction * 300.0);
              if(res.entity) {
                m_mother->activate(res.entity);
              }
              if (m_mother->getActiveKnob()) {
                m_camera->activate(false);
              }
              break;
          }
          break;
        case InputEvent::EVENT_MOUSEUP:
          switch(inputEvent->getMouseButton()) {
            case CoreInput::MOUSE_BUTTON1:
              m_mother->deactivate();
              m_camera->activate(true);
              break;
          }
          break;
        case InputEvent::EVENT_MOUSEMOVE:
          // TODO only if mouse left mouse button down
          Vector3 delta(m_core->getInput()->getMouseDelta().x, m_core->getInput()->getMouseDelta().y, 0);
          m_mother->mouseMove(delta);
          break;
      }
    }
  }

  void Constructor::update() {
    m_mother->update();
  }
}

