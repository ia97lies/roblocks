//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_UNIT_POSITION_H
#define SYNTHETICS_UNIT_POSITION_H

#include <PolyVector3.h>

namespace Synthetics {

  class UnitPosition {
    public:
      UnitPosition(Polycode::Vector3 orientation);
      virtual ~UnitPosition();

      Polycode::Vector3 getShift();
      Polycode::Vector3 getOrientation(); 
      Polycode::Vector3 getRotation(UnitPosition *pos); 

    private:
      Polycode::Vector3 m_orientation;
  };

}

#endif
