//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_SERIALIZER_H
#define SYNTHETICS_SERIALIZER_H

#include "Compound.hpp"
#include "Writer.hpp"

namespace Synthetics {
  class Serializer {
    public:
      Serializer(Compound *compound, Writer *writer);
      virtual ~Serializer();
  };
}

#endif
