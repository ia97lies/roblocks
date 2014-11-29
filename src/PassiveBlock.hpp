//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_PASSIVE_BLOCK_H
#define SYNTHETICS_PASSIVE_BLOCK_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Unit.hpp"

namespace Synthetics {
  namespace Units {
    namespace Passive {

      class Block : public Unit {
        public:
          Block(::Polycode::Core *core, ::Polycode::Scene *scene);
          virtual ~Block();

          virtual int noOfFaces();
          virtual ::Polycode::Vector3 getOrientation(int face);
          virtual void addUnit(int face, Unit *unit);
          virtual Unit *getUnit(int face);
          virtual void handleEvent(::Polycode::Event *event);
      };

    }
  }
}

#endif
