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

          virtual std::string getName(); 
          virtual int getNoParts();
          virtual Part *getPart(int i);
          virtual void enable(bool on); 

          virtual void update(Plug *sendingPlug, Polycode::Vector3 delta);

        private:
          Part *m_body;
          Plug *m_markerPlug;

          void shield(); 
      };

    }
  }
}

#endif
