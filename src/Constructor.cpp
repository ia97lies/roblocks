//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Constructor.hpp"

using namespace Polycode;

namespace Synthetics {
  Constructor::Constructor(Core *core, CollisionScene *scene, MovingCamera *camera, Compounds::Factory *factory) : EventHandler() {

    m_core = core;
    m_scene = scene;
    m_camera = camera;
    m_factory = factory;
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
              // mother->remove()
              break;
            case KEY_a:
              // add current selected compound to current active compound
              // if mother == NULL {
              //   mother = factory->createCompound("<selected-compound-name>")
              // }
              // else {
              //   new = factory->createCompound(selected compound)
              //   mother->add(new)
              // }
              break;
            case KEY_r:
              // rotate active compound around plug right side
              // mother->rotate(90);
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

