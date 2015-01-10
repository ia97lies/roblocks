//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_KNOB_H
#define SYNTHETICS_KNOB_H

#include "PolyEntity.h"
#include "Compound.hpp"

namespace Synthetics {
  class Knob {
    public:
      virtual ~Knob() {}

      virtual Polycode::Entity *getShape() = 0;
      virtual void handleInput(Polycode::Vector3 delta) = 0;
  };
}

#endif

