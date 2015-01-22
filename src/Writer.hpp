//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_WRITER_H
#define SYNTHETICS_WRITER_H

#include "Compound.hpp"

namespace Synthetics {
  class Writer {
    public:
      virtual ~Writer() {};
      virtual void write(Compound *compound) = 0;
  };
}

#endif
