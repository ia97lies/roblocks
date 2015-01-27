//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_COMPONENTPRINTER_H
#define SYNTHETICS_COMPONENTPRINTER_H

#include "Printer.hpp"
#include "Writer.hpp"
#include "Components/Factory.hpp"

namespace Synthetics {
  class ComponentPrinter : public Printer {
    public:
      ComponentPrinter(Writer *writer);
      virtual ~ComponentPrinter();
      virtual void write(Compound *parent, Compound *compound);

    private:
      bool isMotherCreated;
      Writer *m_writer;
  };
}

#endif
