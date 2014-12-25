//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_COMPOUNDS_PASSIVE_HUB_H
#define SYNTHETICS_COMPOUNDS_PASSIVE_HUB_H

#include "Component.hpp"

namespace Synthetics {
  namespace Components {
    namespace Passive {

      class Hub : public Component {
        public:
          Hub();
          virtual ~Hub();

          virtual int getNoParts();
          virtual Part *getPart(int i);

        private:
          Part *m_body;
      };

    }
  }
}

#endif
