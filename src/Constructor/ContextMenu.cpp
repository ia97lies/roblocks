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
      m_menu->setPosition(100,100);
      m_menu->addOption("Add", 1);
      m_menu->addOption("Remove", 1);
      m_menu->addOption("Rotate", 1);
      scene->addChild(m_menu);
      m_menu->enabled = false;

      activate();
    }

    ContextMenu::~ContextMenu() {}

    void ContextMenu::handleEvent(Polycode::Event *e) {
      if(e->getDispatcher() == m_menu) {
        switch(e->getEventCode()) {
          case UIEvent::OK_EVENT:
            fprintf(stderr, "XXXXXX2\n");
            break;
        }
      }
    }

    void ContextMenu::activate() {
      if (!m_menu->enabled) {
        //m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
        m_menu->addEventListener(this, UIEvent::OK_EVENT);
        /* show the context menu */
        m_menu->enabled = true;
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


