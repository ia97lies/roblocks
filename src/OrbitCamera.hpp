//----------------------------------------------------------------------------
// The MIT License
// Took the basics from Polycode Examples
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_ORBIT_CAMERA_H
#define SYNTHETICS_ORBIT_CAMERA_H

#include <Polycode.h>
#include "PolycodeView.h"

#include "MovingCamera.hpp"

namespace Synthetics {

  class OrbitCamera : public MovingCamera {
    public:
      OrbitCamera(Polycode::Core *core, Polycode::Scene *scene);
      ~OrbitCamera();
      virtual void handleEvent(Polycode::Event *e);
      virtual void updateTarget(Polycode::Vector3 pos);
      virtual void update(); 
      virtual void activate(bool on);
      virtual bool isActive(); 

    private:
      bool m_on;
      Polycode::Core *m_core;
      Polycode::Scene *m_scene;
      Polycode::Vector3 m_position;
      Polycode::Vector3 m_target;
      float m_x;
      float m_y;
      float m_distance;
      bool m_mouseClick;
      Polycode::SceneLight *m_light;
      Polycode::SceneSoundListener *m_soundListener;

      float clamp(float angle, float min, float max);
  };

}

#endif
