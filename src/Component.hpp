//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_COMPONENT_H
#define SYNTHETICS_COMPONENT_H

#include <vector>
#include "Compound.hpp"
#include "Part.hpp"

namespace Synthetics {
  class Component : public Compound {
    public:
      virtual ~Component() {};

      virtual int getNoParts() = 0;
      virtual Part *getPart(int i) = 0;
    private:
  };
}

#endif
