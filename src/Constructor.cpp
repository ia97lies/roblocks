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
    m_curFace = 0;

    // todo mother block should be exchangable
    m_mother = m_curUnit = m_factory->createUnit("Passive.Block", m_core, m_scene);
    ScenePrimitive *shape = m_curUnit->getPolycodeObject();
    m_curUnit->setActive(true);
    m_scene->addCollisionChild(shape);
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
              if (m_curUnit->noChilds() == 1 && m_curUnit != m_mother) {
                Unit *selectedUnit = NULL;
                for (int i = 0; i < m_curUnit->noFaces(); i++) {
                  if (m_curUnit->getUnit(i)) {
                    selectedUnit = m_curUnit->getUnit(i); 
                    selectedUnit->setActive(true);
                    break;
                  }
                }
                ScenePrimitive *shape = m_curUnit->getPolycodeObject();
                delete m_curUnit;
                m_curUnit = selectedUnit;
                m_curUnit->setActiveFace(0);
              }
              break;
            case KEY_s:
              m_curFace += 1;
              if (m_curFace > m_curUnit->noFaces() - 1) {
                m_curFace = 0;
              }
              m_curUnit->setActiveFace(m_curFace);
              break;
            case KEY_a:
              Unit *newUnit = m_factory->createUnit("Passive.Block", m_core, m_scene);
              if (!m_curUnit->addUnit(newUnit)) {
                delete newUnit;
              }
              break;
          }
          break;
        case InputEvent::EVENT_MOUSEDOWN:
          switch(inputEvent->getMouseButton()) {
            case CoreInput::MOUSE_BUTTON1:
              Ray ray = m_scene->projectRayFromCameraAndViewportCoordinate(m_scene->getActiveCamera(), inputEvent->mousePosition);
              RayTestResult res = m_scene->getFirstEntityInRay(ray.origin, ray.direction * 100.0);
              if(res.entity) {
                Unit *selectedUnit = (Unit *)res.entity->getUserData();
                if (selectedUnit) {
                  m_curUnit->setActive(false);
                  selectedUnit->setActive(true);
                  m_curUnit = selectedUnit;
                  m_curUnit->setActiveFace(0);
                }
                else {
                  m_curUnit->setActiveFace(res.entity);
                }
              }
              break;
          }
      }
    }
  }
}
