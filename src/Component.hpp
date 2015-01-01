//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_COMPONENT_H
#define SYNTHETICS_COMPONENT_H

#include "PolyEntity.h"
#include "Compound.hpp"
#include "Part.hpp"

namespace Synthetics {
  class Component : public Compound {
    public:
      Component();
      virtual ~Component();

      virtual int getNoParts() = 0;
      virtual Part *getPart(int i) = 0;
      virtual void enable(bool on) = 0;
      virtual Part *getPartByPlug(Polycode::Entity *plugShape);
  };
}

#endif
