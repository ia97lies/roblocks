//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Constructor/ContextMenu.hpp"

#include "CommandNone.hpp"

using namespace Polycode;

namespace Synthetics {
  namespace Constructor {
    ContextMenu::ContextMenu(Core *core, Configurator *conf) {
      m_on = false;
      m_core = core;
      m_conf = conf;

      m_scene = new PhysicsScene2D(0.01, 50);
      m_scene->getActiveCamera()->setOrthoSize(m_conf->getWidth(), m_conf->getHeight());

      //SceneImage *label = new SceneImage("Resources/Icons/add.png");
      //SceneLabel *label = new SceneLabel("ffooooooooo", 14);
      //m_scene->addCollisionChild(label, PhysicsScene2DEntity::ENTITY_RECT);
      /* TODO build up menu and display menu */

      m_menu = new Menu();
      m_menu->addEntry(new MenuEntry(new CommandNone(), new SceneImage("Resources/Icons/Add.png")));
      m_menu->addEntry(new MenuEntry(new CommandNone(), new SceneImage("Resources/Icons/Delete.png")));
      m_menu->addEntry(new MenuEntry(new CommandNone(), new SceneImage("Resources/Icons/Rotate.png")));

      /*
      SceneImage *shape = new SceneImage("Resources/Icons/Add.png");
      shape->setRotationEuler(Vector3(0.0, 0.0, 45.0));
      m_scene->addCollisionChild(shape, PhysicsScene2DEntity::ENTITY_RECT);
      */
      //m_scene->trackCollisionChild(shape, PhysicsScene2DEntity::ENTITY_RECT);
      //activate();
    }

    ContextMenu::~ContextMenu() {}

    void ContextMenu::handleEvent(Polycode::Event *e) {
      if(e->getDispatcher() == m_core->getInput()) {
        InputEvent *inputEvent = (InputEvent*)e;

        switch(e->getEventCode()) {
          case InputEvent::EVENT_MOUSEMOVE:
            {
              /* TODO: Highlight menu entries on hoover. */

              Vector2 mouse = m_core->getInput()->getMousePosition();
              Ray ray = m_scene->projectRayFromCameraAndViewportCoordinate(m_scene->getActiveCamera(), mouse);

              SceneEntity * entity = m_scene->getEntityAtPosition(ray.origin.x, ray.origin.y);
              if(entity) {
                entity->setColor(1.0, 0.0, 0.0, 1.0);
              }
            }
            break;
          case InputEvent::EVENT_MOUSEDOWN:
            {
              /* TODO: execute command and leave context menu */
            }
            break;
        }
      }
    }

    void ContextMenu::activate() {
      if (!m_on) {
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEUP);
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
        /* show the context menu */
        m_on = true;
      }
    } 

    void ContextMenu::deactivate() {
      if (m_on) {
        m_core->getInput()->removeAllHandlersForListener(this);
        /* show the context menu */
        m_on = false;
      }
    } 
  }
}


