//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Help.hpp"

using namespace Polycode;

namespace Synthetics {
  Help::Help(Core *core) : EventHandler() {

    m_core = core;
    m_helpScene = NULL;
    m_helpText = new SceneLabel("Help", 32);
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
              if (m_helpScene) {
                delete m_helpScene;
                m_helpScene = NULL;
              }
              break;
            case KEY_F1:
              fprintf(stderr, "XXXXXXXXX\n");
              if (!m_helpScene) {
                m_helpScene = new Scene(Scene::SCENE_2D);
                m_helpScene->getActiveCamera()->setOrthoSize(640, 480);
                m_helpScene->addChild(m_helpText);
              }
              break;
          }
          break;
      }
    }
  }
}
