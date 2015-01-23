//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_SERIALIZER_H
#define SYNTHETICS_SERIALIZER_H

#include "Compound.hpp"
#include "Printer.hpp"

namespace Synthetics {
  class Serializer {
    public:
      Serializer(Compound *compound, Printer *printer);
      virtual ~Serializer();
  };
}

#endif
