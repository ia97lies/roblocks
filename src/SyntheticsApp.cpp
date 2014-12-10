//----------------------------------------------------------------------------
// The MIT License
// Took the basics from Polycode Examples
//----------------------------------------------------------------------------

#include "SyntheticsApp.hpp"
#include "Configurator.hpp"
#include "OrbitCamera.hpp"
#include "Constructor.hpp"
#include "HeadUpDisplay.hpp"
#include "Unit.hpp"
#include "UnitFactory.hpp"

using namespace Polycode;

namespace Synthetics {
  SyntheticsApp::SyntheticsApp(PolycodeView *view) {
    UnitFactory *factory = UnitFactory::get();

    m_conf = new Configurator(factory);

    m_core = new POLYCODE_CORE(view, m_conf->getWidth(), m_conf->getHeight(), false, true, 0, 0, 90, 0, true);

    CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
    CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

    m_scene = new CollisionScene();

    m_camera = new OrbitCamera(m_core, m_scene);
    m_core->getInput()->addEventListener(m_camera, InputEvent::EVENT_KEYDOWN);
    m_core->getInput()->addEventListener(m_camera, InputEvent::EVENT_MOUSEDOWN);
    m_core->getInput()->addEventListener(m_camera, InputEvent::EVENT_MOUSEUP);
    m_core->getInput()->addEventListener(m_camera, InputEvent::EVENT_MOUSEMOVE);

    HeadUpDisplay *hud = new HeadUpDisplay(m_core, m_conf, factory);
    m_core->getInput()->addEventListener(hud, InputEvent::EVENT_KEYDOWN);

    Constructor *constructor = new Constructor(m_core, m_scene, m_camera, factory);
    m_core->getInput()->addEventListener(constructor, InputEvent::EVENT_KEYDOWN);
    m_core->getInput()->addEventListener(constructor, InputEvent::EVENT_MOUSEDOWN);

    m_camera->update();
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
    return m_core->updateAndRender();
  }
}
