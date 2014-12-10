//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_UNIT_H
#define SYNTHETICS_UNIT_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"

namespace Synthetics {

  class Unit : public Polycode::EventHandler {
    public:
      virtual ~Unit() {};

      virtual void init() = 0;
      virtual int noFaces() = 0;
      virtual bool setActiveFace(int face) = 0;
      virtual bool setActiveFace(Polycode::Entity *marker) = 0; 
      virtual bool addUnit(Unit *unit) = 0;
      virtual void linkUnit(Unit *unit) = 0;
      virtual void removeUnit(Unit *unit) = 0;
      virtual Unit *getUnit(int face) = 0;
      virtual void setActive(bool on) = 0;
      virtual int getActiveFace() = 0;
      virtual int noChilds() = 0;

      virtual Polycode::Vector3 getOrientation(int face) = 0;
      virtual Polycode::ScenePrimitive * getPolycodeObject() = 0;
      virtual void handleEvent(Polycode::Event *event) = 0;
  };

  typedef Unit *(*UnitCreateFn)(Polycode::Core *core, Polycode::CollisionScene *scene);
}

#endif
