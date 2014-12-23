//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_ROBOT_H
#define SYNTHETICS_ROBOT_H

#include "PolyVector3.h"
#include "Compound.hpp"

namespace Synthetics {
  class Robot: public Compound {
    public:
      Robot();
      virtual ~Robot();

      void add(Compound *compound);
      void remove();
      void activate(void *plug);
  };
}

#endif
