//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_UNIT_H
#define SYNTHETICS_UNIT_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"

namespace Synthetics {

  class UnitPlugging;

  class Unit : public Polycode::EventHandler {
    public:
      virtual ~Unit() {};

      virtual void init() = 0;
      virtual UnitPlugging *getPlugging() = 0;
      virtual void setActive(bool on) = 0; 
      virtual Polycode::ScenePrimitive * getPolycodeObject() = 0;
      virtual void handleEvent(Polycode::Event *event) = 0;
  };

  typedef Unit *(*UnitCreateFn)(Polycode::Core *core, Polycode::CollisionScene *scene);
}

#endif
