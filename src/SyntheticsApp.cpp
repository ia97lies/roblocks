//----------------------------------------------------------------------------
// The MIT License
// Took the basics from Polycode Examples
//----------------------------------------------------------------------------

#include "SyntheticsApp.hpp"
#include "OrbitCamera.hpp"

namespace synthetics {
  SyntheticsApp::SyntheticsApp(PolycodeView *view) : EventHandler() {

    m_core = new POLYCODE_CORE(view, 640,480,false,true,0,0,90, 0, true);

    CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
    CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

    m_scene = new Scene(Scene::SCENE_3D);

    m_curBox = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1,1,1);
    m_curBox->loadTexture("Resources/pink_texture.png");
    m_curBox->setPosition(0.0, 0.5, 0.0);
    m_scene->addEntity(m_curBox);

    Camera *camera = new OrbitCamera(m_core, m_scene);

    m_core->getInput()->addEventListener(camera, InputEvent::EVENT_KEYDOWN);
    m_core->getInput()->addEventListener(camera, InputEvent::EVENT_KEYUP);

    m_core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
    m_core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);

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
            case KEY_1:
              addChildBox(Vector3(1.0, 0.0, 0.0));
              break;
            case KEY_2:
              addChildBox(Vector3(-1.0, 0.0, 0.0));
              break;
            case KEY_3:
              addChildBox(Vector3(0.0, 1.0, 0.0));
              break;
            case KEY_4:
              addChildBox(Vector3(0.0, -1.0, 0.0));
              break;
            case KEY_5:
              addChildBox(Vector3(0.0, 0.0, 1.0));
              break;
            case KEY_6:
              addChildBox(Vector3(0.0, 0.0, -1.0));
              break;

          }
          break;
      }
    }
  }

  void SyntheticsApp::addChildBox(Vector3 orientation) {
    // XXX: After a couple of cubes it stops rendering the new one. But the childs are
    // there and the camera follows the invisible boxes.
    // TODO: Inspect Polycode why it stops rendering.
    ScenePrimitive * box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1,1,1);
    box->loadTexture("Resources/pink_texture.png");
    box->setPosition(orientation);
    m_curBox->addChild(box);
    m_curBox = box;
  }

  bool SyntheticsApp::Update() {
    return m_core->updateAndRender();
  }
}
