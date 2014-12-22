//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_COMPOUND_H
#define SYNTHETICS_COMPOUND_H

#include "PolyVector3.h"

namespace Synthetics {
  class Compound {
    public:
      virtual ~Compound() {};

      virtual void add(Compound *compound);
      virtual void remove();
      virtual void activate(void *plug);
  };
}

#endif
