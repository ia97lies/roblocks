//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_PRINTER_H
#define SYNTHETICS_PRINTER_H

#include "Compound.hpp"

namespace Synthetics {
  class Printer {
    public:
      virtual ~Printer() {};
      virtual void write(Compound *parent, Compound *compound) = 0;
  };
}

#endif
