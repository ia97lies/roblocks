//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_BLOCK_H
#define SYNTHETICS_BLOCK_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"

#include "Unit/Event.hpp"

namespace Synthetics {

  class BlockPlugging;

  class Block {
    public:
      virtual ~Block() {};

      virtual void init() = 0;
      virtual BlockPlugging *getPlugging() = 0;
      virtual Polycode::ScenePrimitive * getPolycodeObject() = 0;
      virtual void handleEvent(Unit::Event *event) = 0;
  };

  typedef Block *(*BlockCreateFn)(Polycode::CollisionScene *scene);
}

#endif
