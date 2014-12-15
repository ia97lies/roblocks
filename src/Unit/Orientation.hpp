//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_UNIT_ORIENTATION_H
#define SYNTHETICS_UNIT_ORIENTATION_H

#include <PolyVector3.h>

namespace Synthetics {
  namespace Unit {

    class Orientation {
      public:
        Orientation(Polycode::Vector3 orientation);
        virtual ~Orientation();

        Polycode::Vector3 get(); 
        Polycode::Vector3 getRotation(Orientation *pos); 

      private:
        Polycode::Vector3 m_orientation;
    };

  }
}

#endif
