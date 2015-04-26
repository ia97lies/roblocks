//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Constructor/ContextMenu.hpp"

#include "CommandNone.hpp"

#include "PolyUIEvent.h"

using namespace Polycode;

namespace Synthetics {
  namespace Constructor {
    ContextMenu::ContextMenu(Core *core, Configurator *conf) {
      m_core = core;
      m_conf = conf;

      Scene *scene = new Scene(Scene::SCENE_2D_TOPLEFT);
      scene->doVisibilityChecking(false);
      scene->getDefaultCamera()->frustumCulling = false;
      scene->rootEntity.processInputEvents = true;

      m_menu = new UIMenu(80);
      m_menu->addOption("Add", 1, (void *)1);
      m_menu->addOption("Remove", 1, (void *)2);
      m_menu->addOption("Rotate", 1, (void *)3);
      scene->addChild(m_menu);
      m_menu->enabled = false;
    }

    ContextMenu::~ContextMenu() {}

    void ContextMenu::handleEvent(Polycode::Event *e) {
      if(e->getDispatcher() == m_menu) {
        switch(e->getEventCode()) {
          case UIEvent::OK_EVENT:
            {
              UIMenuItem *item = m_menu->getSelectedItem();
              fprintf(stderr, "XXXXXX2: %p\n", item);
              leave();
            }
            break;
          case UIEvent::CANCEL_EVENT:
            leave();
            break;
        }
      }
    }

    void ContextMenu::activate() {
      if (!m_menu->enabled) {
        //m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
        m_menu->addEventListener(this, UIEvent::OK_EVENT);
        m_menu->addEventListener(this, UIEvent::CANCEL_EVENT);
        /* show the context menu */
        m_menu->enabled = true;
        Vector2 pos = m_core->getInput()->getMousePosition();
        m_menu->setPosition(pos.x, pos.y);
      }
    } 

    void ContextMenu::deactivate() {
      if (m_menu->enabled) {
        m_menu->removeAllHandlersForListener(this);
        /* show the context menu */
        m_menu->enabled = false;
      }
    } 
  }
}


