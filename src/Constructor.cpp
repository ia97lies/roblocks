//----------------------------------------------------------------------------
// The MIT License
// Took the basics from Polycode Examples
//----------------------------------------------------------------------------

#include "Constructor.hpp"

namespace Synthetics {
  Constructor::Constructor(Core *core, Scene *scene) : EventHandler() {

    m_core = core;
    m_scene = scene;

    m_curBox = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1,1,1);
    m_curBox->setColor(0.0, 1.0, 1.0, 0.8);
    m_curBox->setPosition(0.0, 0.5, 0.0);
    m_scene->addEntity(m_curBox);
  }

  Constructor::~Constructor() {
  }

  void Constructor::handleEvent(Event *e) {
    if(e->getDispatcher() == m_core->getInput()) {
      InputEvent *inputEvent = (InputEvent*)e;

      switch(e->getEventCode()) {
        case InputEvent::EVENT_KEYDOWN:
          switch (inputEvent->keyCode()) {
            case KEY_1:
              addChildBox(Vector3(1.0, 0.0, 0.0));
              break;
            case KEY_2:
              addChildBox(Vector3(-1.0, 0.0, 0.0));
              break;
            case KEY_3:
              addChildBox(Vector3(0.0, 1.0, 0.0));
              break;
            case KEY_4:
              addChildBox(Vector3(0.0, -1.0, 0.0));
              break;
            case KEY_5:
              addChildBox(Vector3(0.0, 0.0, 1.0));
              break;
            case KEY_6:
              addChildBox(Vector3(0.0, 0.0, -1.0));
              break;

          }
          break;
      }
    }
  }

  void Constructor::addChildBox(Vector3 orientation) {
    // XXX: After a couple of cubes it stops rendering the new one. But the childs are
    // there and the camera follows the invisible boxes.
    // TODO: Inspect Polycode why it stops rendering.
    ScenePrimitive * box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1,1,1);
    box->setPosition(orientation);
    m_curBox->addChild(box);
    m_curBox = box;
  }
}
