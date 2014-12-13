//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_UNIT_POSITION_H
#define SYNTHETICS_UNIT_POSITION_H

#include <PolyVector3.h>

namespace Synthetics {

  class UnitPosition {
    public:
      UnitPosition(Polycode::Vector3 shift, Polycode::Vector3 orientation);
      virtual ~UnitPosition();

      Polycode::Vector3 getShift();

    private:
      Polycode::Vector3 m_shift;
  };

}

#endif
