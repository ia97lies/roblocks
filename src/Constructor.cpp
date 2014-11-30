//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Constructor.hpp"

using namespace Polycode;

namespace Synthetics {
  Constructor::Constructor(Core *core, Scene *scene, UnitFactory *factory) : EventHandler() {

    m_core = core;
    m_scene = scene;
    m_factory = factory;

    Unit *block = m_factory->createUnit("Passive.Block", m_core, m_scene);
    m_curBox = block->getPolycodeObject();
    m_scene->addEntity(m_curBox);

    m_curFace = 0;
    m_marker = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.1,0.1,0.1);
    m_marker->setColor(1.0, 0.0, 0.0, 1.0);
    m_marker->setPosition(block->getOrientation(m_curFace) * 0.6);
    m_curBox->addChild(m_marker);
  }

  Constructor::~Constructor() {
  }

  void Constructor::handleEvent(Event *e) {
    if(e->getDispatcher() == m_core->getInput()) {
      InputEvent *inputEvent = (InputEvent*)e;

      switch(e->getEventCode()) {
        case InputEvent::EVENT_KEYDOWN:
          switch (inputEvent->keyCode()) {
            case KEY_a:
              break;
            case KEY_d:
              break;
            case KEY_w:
              m_curFace += 1;
              if (m_curFace > 3) {
                m_curFace = 0;
              }
              break;
            case KEY_s:
              m_curFace -= 1;
              if (m_curFace < 0) {
                m_curFace = 3;
              }
              break;
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
//          m_marker->setPosition(block->getOrientation(m_curFace) * 0.6);
          break;
      }
    }
  }

  void Constructor::addChildBox(Vector3 orientation) {
    // XXX: After a couple of cubes it stops rendering the new one. But the childs are
    // there and the camera follows the invisible boxes.
    // TODO: Inspect Polycode why it stops rendering.
    m_factory->createUnit("Passive.Block", m_core, m_scene);
    ScenePrimitive * box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1,1,1);
    box->setPosition(orientation);
    m_curBox->addChild(box);
    m_curBox = box;
  }
}
