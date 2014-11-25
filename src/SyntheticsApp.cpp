//----------------------------------------------------------------------------
// The MIT License
// Took the basics from Polycode Examples
//----------------------------------------------------------------------------

#include "SyntheticsApp.hpp"
#include "OrbitCamera.hpp"
#include "Constructor.hpp"

namespace Synthetics {
  SyntheticsApp::SyntheticsApp(PolycodeView *view) {

    m_core = new POLYCODE_CORE(view, 640,480,false,true,0,0,90, 0, true);

    CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
    CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

    m_scene = new Scene(Scene::SCENE_3D);

    Camera *camera = new OrbitCamera(m_core, m_scene);
    m_core->getInput()->addEventListener(camera, InputEvent::EVENT_KEYDOWN);

    Constructor *constructor = new Constructor(m_core, m_scene);
    m_core->getInput()->addEventListener(constructor, InputEvent::EVENT_KEYDOWN);

    camera->update();
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
