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

  class MovingCamera : public Polycode::EventHandler {
    public:
      MovingCamera() : Polycode::EventHandler() {};
      virtual ~MovingCamera() {};
      virtual void updateTarget(Polycode::Vector3 pos) = 0;
      virtual void update() = 0;
      virtual void activate(bool on) = 0;
  };

}

#endif
