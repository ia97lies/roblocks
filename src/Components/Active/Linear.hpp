//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_COMPONENTS_ACTOR_LINEAR_H
#define SYNTHETICS_COMPONENTS_ACTOR_LINEAR_H

#include "Part.hpp"
#include "Component.hpp"

namespace Synthetics {
  namespace Components {
    namespace Active {

      class Linear : public Component {
        public:
          Linear();
          virtual ~Linear();

          virtual std::string getName(); 
          virtual int getNoParts();
          virtual Part *getPart(int i);
          virtual void enable(bool on); 
          // virtual Joint *getJoint(); 

          virtual void update(Plug *sendingPlug, Polycode::Vector3 delta);

        private:
          Part *m_body[2];
      };

    }
  }
}

#endif
