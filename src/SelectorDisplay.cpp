//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Robot.hpp"
#include "SelectorDisplay.hpp"

using namespace Polycode;

namespace Synthetics {
  SelectorDisplay::SelectorDisplay(Core *core, Configurator *conf, Components::Factory *factory) : EventHandler() {
    m_conf = conf;
    m_core = core;
    m_factory = factory;

    m_core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);

    float border = 10;
    float height = 100;
    float length = m_conf->getWidth();

    m_hudScene = new Scene(Scene::SCENE_2D);
    m_scene = new CollisionScene();
    m_hudScene->getActiveCamera()->setOrthoSize(m_conf->getWidth(), m_conf->getHeight());
    ScenePrimitive *shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, length, height);
    m_hudScene->addChild(shape);
    shape->setColor(0.5, 0.5, 0.5, 0.3);
    shape->setPosition(0, -m_conf->getHeight()/2  + height/2 + border);

    m_index = 0;
    m_text = factory->getNames().at(m_index);
    m_label = new SceneLabel("< "+ m_text + " >", 16);
    //m_hudScene->addChild(m_label);

    m_scene->getDefaultCamera()->setPosition(9,9,9);
    m_scene->getDefaultCamera()->lookAt(Vector3(0, 0, 0));
    m_scene->getDefaultCamera()->cameraShift = Vector2(0.0, 1.0 - (1.0/m_conf->getHeight() * (m_conf->getHeight()/2 + height/2 + border)));

    m_polycodeFacade = new PolycodeFacade(core, m_scene);
    for (int i = 0; i < m_factory->getNames().size(); i++) {
      m_components.push_back(m_factory->createComponent(m_factory->getNames().at(i)));
      Robot::constructGraphic(m_polycodeFacade, NULL, m_components.at(i));
      m_components.at(i)->enable(false);
      m_components.at(i)->getPart(0)->getShape()->setPosition(0,0,0);
    }
    m_components.at(m_index)->enable(true);
  }

  SelectorDisplay::~SelectorDisplay() {
  }

  void SelectorDisplay::handleEvent(Event *e) {
    if(e->getDispatcher() == m_core->getInput()) {
      InputEvent *inputEvent = (InputEvent*)e;

      m_components.at(m_index)->enable(false);
      switch(e->getEventCode()) {
        case InputEvent::EVENT_KEYDOWN:
          switch (inputEvent->keyCode()) {
            case KEY_LEFT:
              if (m_index > 0) {
                --m_index;
              }
              break;
            case KEY_RIGHT:
              if (m_index < m_factory->getNames().size()-1) {
                ++m_index;
              }
              break;
          }
          break;
      }
      m_text = m_factory->getNames().at(m_index);
      m_label->setText("< "+ m_text + " >");
      m_components.at(m_index)->enable(true);
    }
  }

  std::string SelectorDisplay::getText() {
    return m_text;
  }

  void SelectorDisplay::turnOn(bool on) {
    m_hudScene->setEnabled(on);
    m_scene->setEnabled(on);
    if (on) {
      m_core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
    }
    else {
      m_core->getInput()->removeEventListener(this, InputEvent::EVENT_KEYDOWN);
    }
  }
}
