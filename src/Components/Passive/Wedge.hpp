//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_COMPONENTS_PASSIVE_WEDGE_H
#define SYNTHETICS_COMPONENTS_PASSIVE_WEDGE_H

#include "Part.hpp"
#include "Component.hpp"

namespace Synthetics {
  namespace Components {
    namespace Passive {

      class Wedge : public Component {
        public:
          Wedge();
          virtual ~Wedge();

          virtual std::string getName(); 
          virtual int getNoParts();
          virtual Part *getPart(int i); 
          virtual void enable(bool on); 
          virtual void send();
          virtual void update(Polycode::Vector3 delta);

        private:
          Part *m_body[3];
          Polycode::Vector3 m_input;
          Polycode::Vector3 m_output;
      };

    }
  }
}

#endif
