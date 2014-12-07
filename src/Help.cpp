//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Help.hpp"

using namespace Polycode;

namespace Synthetics {
  Help::Help(Core *core) : EventHandler() {

    m_core = core;
    m_helpScene = new Scene(Scene::SCENE_2D);
    m_helpScene->getActiveCamera()->setOrthoSize(640, 480);
    m_helpText = new SceneLabel("Help", 32);
    m_helpScene->addChild(m_helpText);
    m_helpText->enabled = false;
    m_helpText->visible = false;
  }

  Help::~Help() {
  }

  void Help::handleEvent(Event *e) {
    if(e->getDispatcher() == m_core->getInput()) {
      InputEvent *inputEvent = (InputEvent*)e;

      switch(e->getEventCode()) {
        case InputEvent::EVENT_KEYDOWN:
          switch (inputEvent->keyCode()) {
            case KEY_ESCAPE:
              m_helpText->enabled = false;
              m_helpText->visible = false;
              break;
            case KEY_F1:
              m_helpText->enabled = true;
              m_helpText->visible = true;
              break;
          }
          break;
      }
    }
  }
}
