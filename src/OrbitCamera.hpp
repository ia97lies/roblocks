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
#include "Camera.h"

using namespace Polycode;

namespace Synthetics {

  class OrbitCamera : public Camera {
    public:
      OrbitCamera(Core *core, Scene *scene);
      ~OrbitCamera();
      virtual void handleEvent(Event *e);
      virtual void updateTarget(Vector3 pos);
      virtual void update(); 

    private:
      Core *m_core;
      Scene *m_scene;
      float m_pitch;
      float m_yaw;
      float m_distance;
      btVector3 m_upVector;
      Vector3 m_position;
      Vector3 m_target;

      void rotate(float &angle, float value);
  };

}

#endif
