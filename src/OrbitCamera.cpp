//----------------------------------------------------------------------------
// The MIT License
// Took the basics from Polycode Examples
//----------------------------------------------------------------------------

#include "OrbitCamera.hpp"

using namespace Polycode;

namespace Synthetics {

  OrbitCamera::OrbitCamera(Core *core, Scene *scene) : MovingCamera() {

    m_core = core;
    m_scene = scene;

    m_x = 20.0f;
    m_y = 0.0f;
    m_distance = 15.0f;
    m_position = Vector3(0.0f, 0.0f, -m_distance);
    m_upVector = btVector3(0.0f, 1.0f, 0.0f);
    m_target = Vector3(0.0f, 0.0f, 0.0f);

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
            case KEY_LEFT:
              rotate(m_y, +CAMERA_STEP_SIZE); 
              break;
            case KEY_RIGHT:
              rotate(m_y, -CAMERA_STEP_SIZE);
              break;
            case KEY_DOWN:
              rotate(m_x, +CAMERA_STEP_SIZE);
              break;
            case KEY_UP:
              rotate(m_x, -CAMERA_STEP_SIZE);
              break;
            case KEY_HOME:
              m_distance -= CAMERA_STEP_SIZE;
              break;
            case KEY_END:
              m_distance += CAMERA_STEP_SIZE;
              break;
          }
          update();
          break;
      }
    }
  }

  void OrbitCamera::rotate(float &angle, float value) {
    angle -= value;
    if (angle < -360) angle += 360; 
    if (angle >= 360) angle -= 360;
  }


  void OrbitCamera::update() {
    Quaternion *rotation = new Quaternion();
    rotation->fromAxes(m_x, m_y, 0);
    Vector3 position = rotation->applyTo(Vector3(0.0, 0.0, -m_distance)) + m_target;
    m_scene->getDefaultCamera()->setPosition(position);
    m_scene->getDefaultCamera()->setRotationQuat(rotation->w, rotation->x, rotation->y, rotation->z);
    m_scene->getDefaultCamera()->lookAt(m_target);
  }
}
