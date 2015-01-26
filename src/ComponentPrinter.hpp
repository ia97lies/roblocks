//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_COMPONENTPRINTER_H
#define SYNTHETICS_COMPONENTPRINTER_H

#include "Printer.hpp"

namespace Synthetics {
  class ComponentPrinter : public Printer {
    public:
      ComponentPrinter();
      virtual ~ComponentPrinter();
      virtual void write(Compound *parent, Compound *compound);
  };
}

#endif
