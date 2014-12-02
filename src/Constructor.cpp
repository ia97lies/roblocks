//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Constructor.hpp"

using namespace Polycode;

namespace Synthetics {
  Constructor::Constructor(Core *core, CollisionScene *scene, UnitFactory *factory) : EventHandler() {

    m_core = core;
    m_scene = scene;
    m_factory = factory;

    m_selectedUnit = m_factory->createUnit("Passive.Block", m_core, m_scene);
    ScenePrimitive *shape = m_selectedUnit->getPolycodeObject();
    m_scene->addCollisionChild(shape);

    m_curFace = 0;
    m_marker = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.5,0.5,0.5);
    m_marker->setColor(0.8, 0.2, 0.2, 1.0);
    m_marker->setPosition(m_selectedUnit->getOrientation(m_curFace) * 0.3);
    shape->addChild(m_marker);
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
              m_selectedUnit->addUnit(m_curFace, newUnit);
              break;

          }
          m_marker->setPosition(m_selectedUnit->getOrientation(m_curFace) * 0.3);
          //fprintf(stderr, "Unit: %p\n", m_selectedUnit);
          break;
        case InputEvent::EVENT_MOUSEDOWN:
          Ray ray = m_scene->projectRayFromCameraAndViewportCoordinate(m_scene->getActiveCamera(), inputEvent->mousePosition);
          RayTestResult res = m_scene->getFirstEntityInRay(ray.origin, ray.direction * 100.0);
           if(res.entity) {
             res.entity->setColor(1.0, 0.0,0.0,1.0);
           }
          break;
      }
    }
  }
}
