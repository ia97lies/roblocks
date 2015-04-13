//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Display.hpp"

using namespace Polycode;

namespace Synthetics {
  namespace ShowKeyHits {

    Display::Display(Core *core, Configurator *conf) {
      m_core = core;
      m_conf = conf;

      m_scene = new Scene(Scene::SCENE_2D);
      m_scene->getActiveCamera()->setOrthoSize(m_conf->getWidth(), m_conf->getHeight());

      m_i = 0;
      m_label[0] = new KeyLabel();
      m_label[1] = new KeyLabel();
      m_label[0]->setPosition(-m_conf->getWidth()/2 +50, -m_conf->getHeight()/2 + 140);
      m_label[1]->setPosition(-m_conf->getWidth()/2 +50, -m_conf->getHeight()/2 + 120);
      m_scene->addChild(m_label[0]);
      m_scene->addChild(m_label[1]);

      activate(m_conf->getDisplayKeyHits());

    }

    Display::~Display() {}

    void Display::handleEvent(Polycode::Event *e) {
      if(e->getDispatcher() == m_core->getInput()) {
        InputEvent *inputEvent = (InputEvent*)e;
        switch(e->getEventCode()) {
          case InputEvent::EVENT_KEYDOWN:
            switch (inputEvent->keyCode()) {
              case KEY_DELETE:
                {
                  m_label[m_i]->setLabel("Key rel");
                }
                break;
              case KEY_RETURN:
                {
                  m_label[m_i]->setLabel("Key return");
                }
                break;
              case KEY_UP:
                {
                  m_label[m_i]->setLabel("Arrow up");
                }
                break;
              case KEY_DOWN:
                {
                  m_label[m_i]->setLabel("Arrow down");
                }
                break;
              case KEY_LEFT:
                {
                  m_label[m_i]->setLabel("Arrow left");
                }
                break;
              case KEY_RIGHT:
                {
                  m_label[m_i]->setLabel("Arrow right");
                }
                break;
              case KEY_o:
                {
                  m_label[m_i]->setLabel("Key o");
                }
                break;
              case KEY_u:
                {
                  m_label[m_i]->setLabel("Key u");
                }
                break;
              case KEY_r:
                {
                  m_label[m_i]->setLabel("Key r");
                }
                break;
            }
            break;
          case InputEvent::EVENT_MOUSEDOWN:
            switch(inputEvent->getMouseButton()) {
              case CoreInput::MOUSE_BUTTON1:
                {
                  m_label[m_i]->setLabel("Left mouse button");
                }
                break;
            }
            break;
        }
      }
      m_i = (m_i + 1) % 2;
    }

    void Display::update(Number dt) {
      if (m_on) {
        m_label[0]->update(dt);
        m_label[1]->update(dt);
      }
    }

    void Display::activate(bool on) {
      m_on = on;
      if (m_on) {
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
      }
      else {
        m_core->getInput()->removeAllHandlersForListener(this);
      }
    }

  }
}
