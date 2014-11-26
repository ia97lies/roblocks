//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CAMERA_H
#define SYNTHETICS_CAMERA_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "bullet/LinearMath/btVector3.h"
#include "bullet/LinearMath/btMatrix3x3.h"
#include "bullet/LinearMath/btQuaternion.h"

namespace Synthetics {

#define RADIANS_PER_DEGREE 0.01745329f
#define CAMERA_STEP_SIZE 5.0f

  class MovingCamera : public ::Polycode::EventHandler {
    public:
      MovingCamera() : ::Polycode::EventHandler() {};
      virtual ~MovingCamera() {};
      virtual void updateTarget(::Polycode::Vector3 pos) = 0;
      virtual void update() = 0;
  };

}

#endif
