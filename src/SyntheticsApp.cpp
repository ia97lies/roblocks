//----------------------------------------------------------------------------
// The MIT License
// Took the basics from Polycode Examples
//----------------------------------------------------------------------------

#include "SyntheticsApp.hpp"
#include "Configurator.hpp"
#include "Constructor/Display.hpp"
#include "Components/Factory.hpp"
#include "Recorder/PlayEvents.hpp"

using namespace Polycode;

namespace Synthetics {
  SyntheticsApp::SyntheticsApp(PolycodeView *view) {
    Components::Factory *factory = Components::Factory::get();

    m_conf = new Configurator(factory);

    m_core = new POLYCODE_CORE(view, m_conf->getWidth(), m_conf->getHeight(), false, true, 6, 16, 90, 0, true);

    CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
    CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
    CoreServices::getInstance()->getResourceManager()->addDirResource("Resources", false);
    CoreServices::getInstance()->getConfig()->loadConfig("Polycode", "Resources/Assets/UIThemes/dark/theme.xml");
    CoreServices::getInstance()->getResourceManager()->addArchive("Resources/Assets");

    SceneLabel::defaultAnchor = Vector3(-1.0, -1.0, 0.0);
    SceneLabel::defaultPositionAtBaseline = true;
    SceneLabel::defaultSnapToPixels = true;
    SceneLabel::createMipmapsForLabels = false;

    CoreServices::getInstance()->getRenderer()->setAmbientColor(1, 1, 1);

    m_constructor = new Constructor::Display(m_core, m_conf, factory);
    m_displayKeyHits = new ShowKeyHits::Display(m_core, m_conf);
    m_recordEvents = new Recorder::RecordEvents(m_core, m_conf);
    m_playEvents = new Recorder::PlayEvents(m_core, m_conf);
  }

  SyntheticsApp::~SyntheticsApp() {
  }

  void SyntheticsApp::handleEvent(Event *e) {
    if(e->getDispatcher() == m_core->getInput()) {
      InputEvent *inputEvent = (InputEvent*)e;

      switch(e->getEventCode()) {
        case InputEvent::EVENT_KEYDOWN:
          switch (inputEvent->keyCode()) {
              break;
          }
          break;
      }
    }
  }

  bool SyntheticsApp::Update() {
    //TODO: have a look into pattern book how to solve this properly
    Number dt = m_playEvents->emitEvent();
    if (dt == -1) {
      dt = m_core->getElapsed();
    }
    m_constructor->update(dt);
    m_displayKeyHits->update(dt);
    m_recordEvents->update(dt);
    return m_core->updateAndRender();
  }
}

