//----------------------------------------------------------------------------
// The MIT License
// Took the basics from Polycode Examples
//----------------------------------------------------------------------------

#include "OrbitCamera.hpp"

namespace synthetics {

  OrbitCamera::OrbitCamera(Core *core, Scene *scene) : EventHandler() {

    m_core = core;
    m_scene = scene;

    m_pitch = 20.0f;
    m_yaw = 0.0f;
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
              rotate(m_yaw, +CAMERA_STEP_SIZE); 
              break;
            case KEY_RIGHT:
              rotate(m_yaw, -CAMERA_STEP_SIZE);
              break;
            case KEY_UP:
              rotate(m_pitch, +CAMERA_STEP_SIZE);
              break;
            case KEY_DOWN:
              rotate(m_pitch, -CAMERA_STEP_SIZE);
              break;

          }
          update();
          break;
      }

    }
  }

  void OrbitCamera::rotate(float &angle, float value) {
    angle -= value; 
    if (angle < 0) angle += 360; 
    if (angle >= 360) angle -= 360;
  }


  void OrbitCamera::update() {
    float pitch = m_pitch * RADIANS_PER_DEGREE;
    float yaw = m_yaw * RADIANS_PER_DEGREE;

    // did this with bullets linear math
    // TODO: make this with pure Polycode so a Lua example would be possible as
    //       well.
    btQuaternion rotation(m_upVector, yaw);
    btVector3 position(0, 0, -m_distance);
    btVector3 forward(position[0], position[1], position[2]);
    if (forward.length2() < SIMD_EPSILON) {
      forward.setValue(1.f,0.f,0.f);
    }
    btVector3 right = m_upVector.cross(forward);
    btQuaternion roll(right, - pitch);
    position = btMatrix3x3(rotation) * btMatrix3x3(roll) * position;

    m_position.x = position.getX();
    m_position.y = position.getY();
    m_position.z = position.getZ();
    m_position += m_target;


    m_scene->getDefaultCamera()->setPosition(m_position);
    m_scene->getDefaultCamera()->lookAt(m_target);
  }
}
