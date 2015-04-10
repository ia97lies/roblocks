//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_KNOB_H
#define SYNTHETICS_KNOB_H

#include "PolyColor.h"
#include "PolyEntity.h"
#include "Compound.hpp"

namespace Synthetics {
  class Knob {
    public:
      virtual ~Knob() {}

      virtual Polycode::Color getColor() { 
        return Polycode::Color(0.0, 1.0, 1.0, 0.5); 
      }
      virtual void activate(bool on) {
        if (on) {
          getShape()->setColor(0.0, 1.0, 1.0, 1.0);
        }
        else {
          getShape()->setColor(0.0, 1.0, 1.0, 0.5);
        }
      }
      virtual Polycode::Entity *getShape() = 0;
      virtual void handleInput(Polycode::Vector3 delta) = 0;
  };
}

#endif

