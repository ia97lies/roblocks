//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

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

    m_core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
    m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);

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
              // delete active compound
              if (m_mother) {
                m_mother->remove();
              }
              break;
            case KEY_a:
              // add current selected compound to current active compound
              Component *compound = m_factory->createComponent(m_selectorDisplay->getText());
              m_mother->add(compound);
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
              break;
          }
      }
    }
  }
}

