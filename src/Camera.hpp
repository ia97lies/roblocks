//----------------------------------------------------------------------------
// The MIT License
// Took the basics from Polycode Examples
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CAMERA_H
#define SYNTHETICS_CAMERA_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "bullet/LinearMath/btVector3.h"
#include "bullet/LinearMath/btMatrix3x3.h"
#include "bullet/LinearMath/btQuaternion.h"

using namespace Polycode;

namespace Synthetics {

#define RADIANS_PER_DEGREE 0.01745329f
#define CAMERA_STEP_SIZE 5.0f

  class Camera : public EventHandler {
    public:
      Camera() : EventHandler() {};
      virtual ~Camera() {};
      virtual void updateTarget(Vector3 pos) = 0;
      virtual void update() = 0;
  };

}

#endif
