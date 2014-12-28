//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_COMPONENTS_PASSIVE_HUB_H
#define SYNTHETICS_COMPONENTS_PASSIVE_HUB_H

#include "Part.hpp"
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
