//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolycodeFacade.hpp"
#include "Part.hpp"
#include "Constructor.hpp"

using namespace Polycode;

namespace Synthetics {

  Constructor::Constructor(Core *core, CollisionScene *scene, MovingCamera *camera, Components::Factory *factory) : EventHandler() {
    m_core = core;
    m_scene = scene;
    m_camera = camera;
    m_factory = factory;
    m_mother = new Robot(new PolycodeFacade(core, scene));
    m_selectedComponent = "Passive.Hub";
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
              Component *compound = m_factory->createComponent(m_selectedComponent);
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

