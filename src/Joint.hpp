//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_JOINT_H
#define SYNTHETICS_JOINT_H

#include "PolyPhysicsScene.h"
#include "PolyVector3.h"

namespace Synthetics {
  class Joint {
    public:
      Joint(int partIndex[2], Polycode::Vector3 pivot[2], Polycode::Vector3 axis[2]);
      virtual ~Joint();

      // FIXME: the problem with this approach is that the call below will fail if
      //        the grafic constructor did not yet drop both parts into scene!
      // virtual Polycode::PhysicsHingeConstraint *getPolycodeJoint();

      virtual void setPhysicJoint(btHingeConstraint *physicJoint);
      virtual btHingeConstraint *getPhysicJoint();
    private:
  };
}

#endif
