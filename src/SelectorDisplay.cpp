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

    m_scene = new CollisionScene();
    m_hudScene = new Scene(Scene::SCENE_2D);
    m_hudScene->getActiveCamera()->setOrthoSize(m_conf->getWidth(), m_conf->getHeight());

    m_index = 0;
    m_text = factory->getNames().at(m_index);
    m_label = new SceneLabel("< "+ m_text + " >", 16);
    m_hudScene->addChild(m_label);
    m_label->setPosition(0, -40);

    m_scene->getDefaultCamera()->setPosition(7,7,7);
    m_scene->getDefaultCamera()->lookAt(Vector3(0, 0, 0));

    m_polycodeFacade = new PolycodeFacade(core, m_scene);
    for (int i = 0; i < m_factory->getNames().size(); i++) {
      m_components.push_back(m_factory->createComponent(m_factory->getNames().at(i)));
      Robot::constructGraphic(m_polycodeFacade, NULL, m_components.at(i));
      m_components.at(i)->enable(false);
      m_scene->addChild(m_components.at(i)->getPart(0)->getShape());
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
  }
}
