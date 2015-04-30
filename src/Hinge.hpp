//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_HINGE_H
#define SYNTHETICS_HINGE_H

#include "HingePoint.hpp"

namespace Synthetics {
  class Hinge {
    public:
      Hinge(HingePoint *point1, HingePoint *point2);
      virtual ~Hinge();

      HingePoint *getPoint(size_t index);

    private:
      HingePoint *m_point[2];
  };
}

#endif
