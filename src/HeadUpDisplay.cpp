//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "HeadUpDisplay.hpp"

using namespace Polycode;

namespace Synthetics {
  HeadUpDisplay::HeadUpDisplay(Core *core, Configurator *conf, UnitFactory *factory) : EventHandler() {
    m_conf = conf;
    m_core = core;
    m_on = false;

    float border = 10;
    float height = 100;
    float length = m_conf->getWidth() - 2 * border;
    Vector4 white(1.0, 1.0, 1.0, 1.0);

    m_hudScene = new Scene(Scene::SCENE_2D);
    m_hudScene->getActiveCamera()->setOrthoSize(m_conf->getWidth(), m_conf->getHeight());
    ScenePrimitive *shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, length, height);
    shape->setColor(1.0, 1.0, 1.0, 0.3);
    shape->setPosition(0, -m_conf->getHeight()/2 + border + height/2);
    m_hudScene->addChild(shape);

    SceneLine *line = new SceneLine(Vector3(-m_conf->getWidth()/2 + border, - m_conf->getHeight()/2 + border + height, 0), 
                                    Vector3(m_conf->getWidth()/2  - border, - m_conf->getHeight()/2 + border + height, 0));
    line->setColor(white.x, white.y, white.z, white.w);
    m_hudScene->addChild(line);
    line = new SceneLine(Vector3(-m_conf->getWidth()/2 + border, - m_conf->getHeight()/2 + border, 0), 
                         Vector3( m_conf->getWidth()/2 - border, - m_conf->getHeight()/2 + border, 0));
    line->setColor(white.x, white.y, white.z, white.w);
    m_hudScene->addChild(line);
    line = new SceneLine(Vector3(-m_conf->getWidth()/2 + border, - m_conf->getHeight()/2 + border, 0), 
                         Vector3(-m_conf->getWidth()/2 + border, - m_conf->getHeight()/2 + border + height, 0));
    line->setColor(white.x, white.y, white.z, white.w);
    m_hudScene->addChild(line);
    line = new SceneLine(Vector3(m_conf->getWidth()/2 - border, - m_conf->getHeight()/2 + border, 0), 
                         Vector3(m_conf->getWidth()/2 - border, - m_conf->getHeight()/2 + border + height, 0));
    line->setColor(white.x, white.y, white.z, white.w);
    m_hudScene->addChild(line);

    m_hudHelp = new SceneLabel("Help Screen", 16);
    m_hudHelp->setPosition(-m_conf->getWidth()/2 + 100, m_conf->getHeight()/2 - 16);
    m_hudHelp->enabled = false;
    m_hudHelp->visible = false;
    m_hudScene->addChild(m_hudHelp);
  }

  HeadUpDisplay::~HeadUpDisplay() {
  }

  void HeadUpDisplay::handleEvent(Event *e) {
    if(e->getDispatcher() == m_core->getInput()) {
      InputEvent *inputEvent = (InputEvent*)e;

      switch(e->getEventCode()) {
        case InputEvent::EVENT_KEYDOWN:
          switch (inputEvent->keyCode()) {
            case KEY_ESCAPE:
              m_on = m_on ? false : true;
              if (m_on) {
                m_hudHelp->enabled = true;
                m_hudHelp->visible = true;
              }
              else {
                m_hudHelp->enabled = false;
                m_hudHelp->visible = false;
              }
              break;
          }
          break;
      }
    }
  }
}
