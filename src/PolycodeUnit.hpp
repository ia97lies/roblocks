//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_POLYCODE_UNIT_H
#define SYNTHETICS_POLYCODE_UNIT_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"

#include "Unit/Event.hpp"

namespace Synthetics {

  class UnitPlugging;

  class PolycodeUnit {
    public:
      virtual ~PolycodeUnit() {};

      virtual void init() = 0;
      virtual UnitPlugging *getPlugging() = 0;
      virtual void setActive(bool on) = 0; 
      virtual Polycode::ScenePrimitive * getPolycodeObject() = 0;
      virtual void handleEvent(Unit::Event *event) = 0;
  };

  typedef PolycodeUnit *(*UnitCreateFn)(Polycode::Core *core, Polycode::CollisionScene *scene);
}

#endif
