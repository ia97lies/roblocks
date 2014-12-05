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

    m_curUnit = m_factory->createUnit("Passive.Block", m_core, m_scene);
    ScenePrimitive *shape = m_curUnit->getPolycodeObject();
    m_curUnit->setActive(true);
    m_scene->addCollisionChild(shape);

    m_marker = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.5,0.5,0.5);
    m_marker->setColor(0.8, 0.2, 0.2, 1.0);
    this->addMarker();
  }

  Constructor::~Constructor() {
  }

  void Constructor::handleEvent(Event *e) {
    if(e->getDispatcher() == m_core->getInput()) {
      InputEvent *inputEvent = (InputEvent*)e;

      switch(e->getEventCode()) {
        case InputEvent::EVENT_KEYDOWN:
          if (m_curUnit != NULL) {
            switch (inputEvent->keyCode()) {
              case KEY_DELETE:
                if (!m_curUnit->haveChilds() && m_curUnit->haveParents()) {
                  ScenePrimitive *shape = m_curUnit->getPolycodeObject();
                  m_scene->removeEntity(shape);
                  delete m_curUnit;
                  m_curUnit = NULL;
                }
                break;
              case KEY_s:
                m_curFace += 1;
                if (m_curFace > m_curUnit->noOfFaces() - 1) {
                  m_curFace = 0;
                }
                m_marker->setPosition(m_curUnit->getOrientation(m_curFace) * 0.3);
                break;
              case KEY_a:
                Unit *newUnit = m_factory->createUnit("Passive.Block", m_core, m_scene);
                if (m_curUnit->addUnit(m_curFace, newUnit)) {
                  m_scene->addCollisionChild(newUnit->getPolycodeObject());
                }
                else {
                  delete newUnit;
                }
                break;
            }
          }
          //fprintf(stderr, "Unit: %p\n", m_curUnit);
          break;
        case InputEvent::EVENT_MOUSEDOWN:
          switch(inputEvent->getMouseButton()) {
            case CoreInput::MOUSE_BUTTON1:
              Ray ray = m_scene->projectRayFromCameraAndViewportCoordinate(m_scene->getActiveCamera(), inputEvent->mousePosition);
              RayTestResult res = m_scene->getFirstEntityInRay(ray.origin, ray.direction * 100.0);
              if(res.entity) {
                Unit *selectedUnit = (Unit *)res.entity->getUserData();
                if (selectedUnit) {
                  if (m_curUnit != NULL) {
                    this->removeMarker();
                    m_curUnit->setActive(false);
                  }
                  selectedUnit->setActive(true);
                  m_curUnit = selectedUnit;
                  this->addMarker();
                }
              }
              break;
          }
      }
    }
  }

  void Constructor::addMarker() {
    ScenePrimitive *shape = m_curUnit->getPolycodeObject();
    m_curFace = 0;
    m_marker->setPosition(m_curUnit->getOrientation(m_curFace) * 0.3);
    shape->addChild(m_marker);
  }

  void Constructor::removeMarker() {
    ScenePrimitive *shape = m_curUnit->getPolycodeObject();
    shape->removeChild(m_marker);
  }
}
