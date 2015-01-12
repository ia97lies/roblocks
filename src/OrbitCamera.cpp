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

    m_core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
    m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
    m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEUP);
    m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);

    m_on = true;
    m_x = 20.0f;
    m_y = 20.0f;
    m_distance = 15.0f;
    m_position = Vector3(0.0f, 0.0f, -m_distance);
    m_target = Vector3(0.0f, 0.0f, 0.0f);
    m_mouseClick = false;

    update();
  }

  OrbitCamera::~OrbitCamera() {
  }

  void OrbitCamera::updateTarget(Vector3 target) {
    m_target = target;
  }

  void OrbitCamera::handleEvent(Event *e) {
    if(e->getDispatcher() == m_core->getInput()) {
      InputEvent *inputEvent = (InputEvent*)e;

      switch(e->getEventCode()) {
        case InputEvent::EVENT_KEYDOWN:
          switch (inputEvent->keyCode()) {
            case KEY_w:
              m_distance -= CAMERA_STEP_SIZE;
              break;
            case KEY_s:
              m_distance += CAMERA_STEP_SIZE;
              break;
          }
          update();
          break;
        case InputEvent::EVENT_MOUSEDOWN:
          switch(inputEvent->getMouseButton()) {
            case CoreInput::MOUSE_BUTTON1:
              m_mouseClick = true;
              break;
          }
          break;
        case InputEvent::EVENT_MOUSEUP:
          switch(inputEvent->getMouseButton()) {
            case CoreInput::MOUSE_BUTTON1:
              m_mouseClick = false;
              break;
          }
          break;
        case InputEvent::EVENT_MOUSEMOVE:
          if (m_mouseClick) {
            m_x += m_core->getInput()->getMouseDelta().x;
            m_y -= m_core->getInput()->getMouseDelta().y;
            clamp(m_y, -20, 80);
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
    Vector3 position = rotation->applyTo(Vector3(0.0, 0.0, -m_distance));
    m_scene->getDefaultCamera()->setPosition(position);
    m_scene->getDefaultCamera()->setRotationQuat(rotation->w, rotation->x, rotation->y, rotation->z);
    m_scene->getDefaultCamera()->lookAt(m_target);
  }

  void OrbitCamera::activate(bool on) {
    if (on && !m_on) {
      m_core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
      m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
      m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEUP);
      m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
    }
    else if (!on && m_on) {
      m_core->getInput()->removeEventListener(this, InputEvent::EVENT_KEYDOWN);
      m_core->getInput()->removeEventListener(this, InputEvent::EVENT_MOUSEDOWN);
      m_core->getInput()->removeEventListener(this, InputEvent::EVENT_MOUSEUP);
      m_core->getInput()->removeEventListener(this, InputEvent::EVENT_MOUSEMOVE);
    }
    m_on = on;
  }
}
