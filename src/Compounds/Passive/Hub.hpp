//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_COMPOUNDS_PASSIVE_HUB_H
#define SYNTHETICS_COMPOUNDS_PASSIVE_HUB_H

#include "Compound.hpp"

namespace Synthetics {
  namespace Compounds {
    namespace Passive {

      class Hub : public Compound {
        public:
          Hub();
          virtual ~Hub();

          virtual void add(Compound *compound);
          virtual void remove();
          virtual void activate(void *plug);
      };

    }
  }
}

#endif