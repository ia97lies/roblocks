//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_PART_H
#define SYNTHETICS_PART_H

#include "PolyEntity.h"
#include "Compound.hpp"

namespace Synthetics {
  class Part : public Compound {
    public:
      virtual ~Part() {};
      
      virtual Polycode::Entity *getShape() = 0;
  };
}

#endif
