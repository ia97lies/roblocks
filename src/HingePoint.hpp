//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_HINGEPOINT_H
#define SYNTHETICS_HINGEPOINT_H

#include "PolyVector3.h"
#include "Part.hpp"

namespace Synthetics {
  class HingePoint {
    public:
      HingePoint(Part *part, Polycode::Vector3 pivot, Polycode::Vector3 axis);
      virtual ~HingePoint();

      Part *getPart();
      Polycode::Vector3 getPivot();
      Polycode::Vector3 getAxis();

    private:
      Part *m_part;
      Polycode::Vector3 m_pivot;
      Polycode::Vector3 m_axis;
  };
}

#endif
