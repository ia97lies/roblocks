//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Robot.hpp"
#include "SelectorDisplay.hpp"

using namespace Polycode;

namespace Synthetics {
  SelectorDisplay::SelectorDisplay(Core *core, Configurator *conf, Components::Factory *factory, ChangeSelection *changeSelection) : EventHandler() {
    m_conf = conf;
    m_core = core;
    m_factory = factory;
    m_changeSelection = changeSelection;

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

    m_light = new SceneLight(SceneLight::POINT_LIGHT, m_scene, 70);
    m_light->setPosition(0,0,0);
    m_light->setLightColor(1,1,1);
    m_scene->addLight(m_light);

    m_index = 0;
    m_text = factory->getNames().at(m_index);
    m_label = new SceneLabel("< "+ m_text + " >", 16);
    m_label->setPosition(-m_label->getTextWidthForString(m_label->getText())/2, -m_conf->getHeight()/2 + 2 * border);
    m_hudScene->addChild(m_label);

    m_scene->getDefaultCamera()->setPosition(0,15,25);
    m_scene->getDefaultCamera()->lookAt(Vector3(0, 0, 0));
    m_scene->getDefaultCamera()->cameraShift = Vector2(0.0, 1.0 - (1.0/m_conf->getHeight() * (m_conf->getHeight()/2 + height/2 + 2 * border)));

    m_polycodeFacade = new PolycodeFacade(core, m_scene);
    for (int i = 0; i < m_factory->getNames().size(); i++) {
      m_components.push_back(m_factory->createComponent(m_factory->getNames().at(i), m_core, m_scene));
      Robot::constructGraphic(m_polycodeFacade, NULL, m_components.at(i));
      for (int j = 0; j < m_components.at(i)->getNoParts(); j++) {
        Robot::constructPlugsGraphic(m_polycodeFacade, m_components.at(i)->getPart(j));
      }
      //m_components.at(i)->enable(false);
      // XXX I AM HERE: place them in x row point camera directly on it, and rotate them to have 2.5 view on it
      // show all and look at the active one
      m_components.at(i)->getPart(0)->getShape()->setPosition(3*i, 0, 0);
    }
    //m_components.at(m_index)->enable(true);
    m_light->setPosition(3*m_index, 5, 7);
    m_components.at(m_index)->getPart(0)->getShape()->setScale(1.5,1.5,1.5);
      m_components.at(m_index)->getPart(0)->getShape()->setPosition(3*m_index, 1, 0);
    m_components.at(m_index)->getPart(0)->getShape()->setRotationEuler(Vector3(0, -45, 0));
  }

  SelectorDisplay::~SelectorDisplay() {
  }

  void SelectorDisplay::handleEvent(Event *e) {
    if(e->getDispatcher() == m_core->getInput()) {
      InputEvent *inputEvent = (InputEvent*)e;

      //m_components.at(m_index)->enable(false);
      m_components.at(m_index)->getPart(0)->getShape()->setScale(1,1,1);
      m_components.at(m_index)->getPart(0)->getShape()->setPosition(3*m_index, 0, 0);
      m_components.at(m_index)->getPart(0)->getShape()->setRotationEuler(0);
      switch(e->getEventCode()) {
        case InputEvent::EVENT_KEYDOWN:
          switch (inputEvent->keyCode()) {
            case KEY_LEFT:
              if (m_index > 0) {
                --m_index;
                m_changeSelection->onChange(m_factory->getNames().at(m_index));
              }
              break;
            case KEY_RIGHT:
              if (m_index < m_factory->getNames().size()-1) {
                ++m_index;
                m_changeSelection->onChange(m_factory->getNames().at(m_index));
              }
              break;
          }
          break;
      }
      m_text = m_factory->getNames().at(m_index);
      m_label->setText("< "+ m_text + " >");
      m_label->setPosition(-m_label->getTextWidthForString(m_label->getText())/2, m_label->getPosition2D().y);
      //m_components.at(m_index)->enable(true);
      m_light->setPosition(3*m_index, 5, 7);
      m_components.at(m_index)->getPart(0)->getShape()->setScale(1.5,1.5,1.5);
      m_components.at(m_index)->getPart(0)->getShape()->setPosition(3*m_index, 1, 0);
      m_components.at(m_index)->getPart(0)->getShape()->setRotationEuler(Vector3(0, -45, 0));
      m_scene->getDefaultCamera()->setPosition(3* m_index, 15, 25);
      m_scene->getDefaultCamera()->lookAt(Vector3(3* m_index, 0, 0));
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
