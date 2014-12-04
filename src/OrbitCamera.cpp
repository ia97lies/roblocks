//----------------------------------------------------------------------------
// The MIT License
// Took the basics from Polycode Examples
//----------------------------------------------------------------------------

#include "OrbitCamera.hpp"
#include <math.h>

using namespace Polycode;

namespace Synthetics {

  OrbitCamera::OrbitCamera(Core *core, Scene *scene) : MovingCamera() {

    m_core = core;
    m_scene = scene;

    m_x = 20.0f;
    m_y = 0.0f;
    m_distance = 15.0f;
    m_position = Vector3(0.0f, 0.0f, -m_distance);
    m_target = Vector3(0.0f, 0.0f, 0.0f);
    m_mouseRightClick = false;

    update();
  }

  OrbitCamera::~OrbitCamera() {
  }

  void OrbitCamera::updateTarget(Vector3 position) {
    m_position = position;
  }

  void OrbitCamera::handleEvent(Event *e) {
    if(e->getDispatcher() == m_core->getInput()) {
      InputEvent *inputEvent = (InputEvent*)e;

      switch(e->getEventCode()) {
        case InputEvent::EVENT_KEYDOWN:
          switch (inputEvent->keyCode()) {
            case KEY_HOME:
              m_distance -= CAMERA_STEP_SIZE;
              break;
            case KEY_END:
              m_distance += CAMERA_STEP_SIZE;
              break;
          }
          update();
          break;
        case InputEvent::EVENT_MOUSEDOWN:
          switch(inputEvent->getMouseButton()) {
            case CoreInput::MOUSE_BUTTON2:
              m_mouseRightClick = true;
              break;
          }
          break;
        case InputEvent::EVENT_MOUSEUP:
          switch(inputEvent->getMouseButton()) {
            case CoreInput::MOUSE_BUTTON2:
              m_mouseRightClick = false;
              break;
          }
          break;
        case InputEvent::EVENT_MOUSEMOVE:
          if (m_mouseRightClick) {
            m_x = inputEvent->getMousePosition().x;
            m_y = inputEvent->getMousePosition().y;
            update();
            break;
          }
      }
    }
  }

  float OrbitCamera::clamp(float angle, float min, float max) {
    if (angle < -360) angle += 360; 
    if (angle >= 360) angle -= 360;
    return clampf(angle, min, max);
  }


  void OrbitCamera::update() {
    Quaternion *rotation = new Quaternion();
    rotation->fromAxes(m_y, m_x, 0);
    Vector3 position = rotation->applyTo(Vector3(0.0, 0.0, -m_distance)) + m_target;
    m_scene->getDefaultCamera()->setPosition(position);
    m_scene->getDefaultCamera()->setRotationQuat(rotation->w, rotation->x, rotation->y, rotation->z);
    m_scene->getDefaultCamera()->lookAt(m_target);
  }
}
