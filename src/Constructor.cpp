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

    m_selectedUnit = m_factory->createUnit("Passive.Block", m_core, m_scene);
    m_curBox = m_selectedUnit->getPolycodeObject();
    m_scene->addEntity(m_curBox);

    m_curFace = 0;
    m_marker = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.5,0.5,0.5);
    m_marker->setColor(1.0, 0.0, 0.0, 1.0);
    m_marker->setPosition(m_selectedUnit->getOrientation(m_curFace) * 0.3);
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
            case KEY_PAGEUP:
              m_curFace += 1;
              if (m_curFace > m_selectedUnit->noOfFaces() - 1) {
                m_curFace = 0;
              }
              break;
            case KEY_PAGEDOWN:
              m_curFace -= 1;
              if (m_curFace < 0) {
                m_curFace = m_selectedUnit->noOfFaces() - 1;
              }
              break;
            case KEY_a:
              Unit *newUnit = m_factory->createUnit("Passive.Block", m_core, m_scene);
              ScenePrimitive *box = newUnit->getPolycodeObject();
              box->setPosition(m_selectedUnit->getOrientation(m_curFace));
              m_curBox->addChild(box);

              break;

          }
          m_marker->setPosition(m_selectedUnit->getOrientation(m_curFace) * 0.3);
          fprintf(stderr, "Unit: %p\n", m_selectedUnit);
          break;
      }
    }
  }

  void Constructor::addChildBox(Vector3 orientation) {
    // XXX: After a couple of cubes it stops rendering the new one. But the childs are
    // there and the camera follows the invisible boxes.
    // TODO: Inspect Polycode why it stops rendering.
    fprintf(stderr, "Unit: %p\n", m_selectedUnit);
    m_factory->createUnit("Passive.Block", m_core, m_scene);
    ScenePrimitive * box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1,1,1);
    box->setPosition(orientation);
    m_curBox->addChild(box);
    m_curBox = box;
  }
}
