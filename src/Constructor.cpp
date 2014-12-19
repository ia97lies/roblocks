//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "BlockPlugging.hpp"
#include "Constructor.hpp"

using namespace Polycode;

namespace Synthetics {
  Constructor::Constructor(Core *core, CollisionScene *scene, MovingCamera *camera, BlockFactory *factory) : EventHandler() {

    m_core = core;
    m_scene = scene;
    m_camera = camera;
    m_factory = factory;

    // todo mother block should be exchangable
    m_mother = m_curBlock = m_factory->createBlock("Passive.Hub", m_scene);
    ScenePrimitive *shape = m_curBlock->getShape();
    m_curBlock->getPlugging()->setActive(true);
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
              if (m_curBlock->getPlugging()->getNoChilds() == 1 && m_curBlock != m_mother) {
                Block *selectedBlock = NULL;
                for (int i = 0; i < m_curBlock->getPlugging()->getNoFaces(); i++) {
                  if (m_curBlock->getPlugging()->getBlock(i)) {
                    selectedBlock = m_curBlock->getPlugging()->getBlock(i); 
                    selectedBlock->getPlugging()->setActive(true);
                    break;
                  }
                }
                ScenePrimitive *shape = m_curBlock->getShape();
                delete m_curBlock;
                m_curBlock = selectedBlock;
                m_curBlock->getPlugging()->setActiveFace(0);
              }
              break;
            case KEY_a:
              Block *newBlock = m_factory->createBlock("Passive.Hub", m_scene);
              if (!m_curBlock->getPlugging()->addBlock(newBlock)) {
                delete newBlock;
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
                Block *selectedBlock = (Block *)res.entity->getUserData();
                if (selectedBlock) {
                  m_curBlock->getPlugging()->setActive(false);
                  selectedBlock->getPlugging()->setActive(true);
                  m_curBlock = selectedBlock;
                  m_curBlock->getPlugging()->setActiveFace(0);
                }
                else {
                  m_curBlock->getPlugging()->setActiveFace(res.entity);
                }
              }
              break;
          }
      }
      //m_camera->updateTarget(m_curBlock->getShape()->getCombinedPosition());
      //m_camera->update();
    }
  }
}
