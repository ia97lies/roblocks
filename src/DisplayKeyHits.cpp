//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "DisplayKeyHits.hpp"

using namespace Polycode;

namespace Synthetics {
  DisplayKeyHits::DisplayKeyHits(Core *core, Configurator *conf) {
    m_core = core;
    m_conf = conf;

      m_scene = new Scene(Scene::SCENE_2D);
      m_scene->getActiveCamera()->setOrthoSize(m_conf->getWidth(), m_conf->getHeight());

      m_i = 0;
      m_label[0] = new SceneLabel("", 18);
      m_label[1] = new SceneLabel("", 18);
      m_label[0]->setPosition(-m_conf->getWidth()/2 +50, -m_conf->getHeight()/2 + 70);
      m_label[1]->setPosition(-m_conf->getWidth()/2 +50, -m_conf->getHeight()/2 + 50);
      m_label[0]->setColor(1, 1, 1, 1);
      m_scene->addChild(m_label[0]);
      m_scene->addChild(m_label[1]);

      activate(true);

  }

  DisplayKeyHits::~DisplayKeyHits() {}

  void DisplayKeyHits::handleEvent(Polycode::Event *e) {
    if(e->getDispatcher() == m_core->getInput()) {
      InputEvent *inputEvent = (InputEvent*)e;
      switch(e->getEventCode()) {
        case InputEvent::EVENT_KEYDOWN:
          switch (inputEvent->keyCode()) {
            case KEY_DELETE:
              {
                m_label[m_i]->setText("Key rel");
              }
              break;
            case KEY_RETURN:
              {
                m_label[m_i]->setText("Key return");
              }
              break;
            case KEY_UP:
              {
                m_label[m_i]->setText("Arrow up");
              }
              break;
            case KEY_DOWN:
              {
                m_label[m_i]->setText("Arrow down");
              }
              break;
            case KEY_LEFT:
              {
                m_label[m_i]->setText("Arrow left");
              }
              break;
            case KEY_RIGHT:
              {
                m_label[m_i]->setText("Arrow right");
              }
              break;
            case KEY_o:
              {
                m_label[m_i]->setText("Key o");
              }
              break;
            case KEY_u:
              {
                m_label[m_i]->setText("Key u");
              }
              break;
            case KEY_r:
              {
                m_label[m_i]->setText("Key r");
              }
              break;
          }
          break;
        case InputEvent::EVENT_MOUSEDOWN:
          switch(inputEvent->getMouseButton()) {
            case CoreInput::MOUSE_BUTTON1:
              {
                m_label[m_i]->setText("Left mouse button");
              }
              break;
          }
          break;
      }
    }
    m_i = (m_i + 1) % 2;
  }

  void DisplayKeyHits::update(Number dt) {}

  void DisplayKeyHits::activate(bool on) {
    if (on) {
      m_core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
      m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
    }
    else if (!on) {
      m_core->getInput()->removeEventListener(this, InputEvent::EVENT_KEYDOWN);
      m_core->getInput()->removeEventListener(this, InputEvent::EVENT_MOUSEDOWN);
    }
  }

}

