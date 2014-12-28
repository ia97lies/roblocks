//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Part.hpp"
#include "Constructor.hpp"

using namespace Polycode;

namespace Synthetics {

  Constructor::Constructor(Core *core, CollisionScene *scene, MovingCamera *camera, Components::Factory *factory) : EventHandler() {
    m_core = core;
    m_scene = scene;
    m_camera = camera;
    m_factory = factory;
    m_mother = new Robot(core, scene);
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
              Component *compound = m_factory->createComponent("Actor.Servo");
              m_mother->add(compound);
              break;
          }
          break;
        case InputEvent::EVENT_MOUSEDOWN:
          switch(inputEvent->getMouseButton()) {
            case CoreInput::MOUSE_BUTTON1:
              // select compound and compound face
              // object = raycast()
              // if object {
              //   mother->activate(object)
              // }
              break;
          }
      }
    }
  }
}

