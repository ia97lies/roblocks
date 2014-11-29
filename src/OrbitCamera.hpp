//----------------------------------------------------------------------------
// The MIT License
// Took the basics from Polycode Examples
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_ORBIT_CAMERA_H
#define SYNTHETICS_ORBIT_CAMERA_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "bullet/LinearMath/btVector3.h"
#include "bullet/LinearMath/btMatrix3x3.h"
#include "bullet/LinearMath/btQuaternion.h"

#include "MovingCamera.hpp"

namespace Synthetics {

  class OrbitCamera : public MovingCamera {
    public:
      OrbitCamera(Polycode::Core *core, Polycode::Scene *scene);
      ~OrbitCamera();
      virtual void handleEvent(Polycode::Event *e);
      virtual void updateTarget(Polycode::Vector3 pos);
      virtual void update(); 

    private:
      Polycode::Core *m_core;
      Polycode::Scene *m_scene;
      Polycode::Vector3 m_position;
      Polycode::Vector3 m_target;
      float m_pitch;
      float m_yaw;
      float m_distance;
      btVector3 m_upVector;

      void rotate(float &angle, float value);
  };

}

#endif
