//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_COMPONENTS_ACTOR_SERVO_H
#define SYNTHETICS_COMPONENTS_ACTOR_SERVO_H

#include "Part.hpp"
#include "Component.hpp"

namespace Synthetics {
  namespace Components {
    namespace Active {

      class Servo : public Component {
        public:
          Servo();
          virtual ~Servo();

          virtual std::string getName(); 
          virtual int getNoParts();
          virtual Part *getPart(int i);
          virtual void enable(bool on); 
          // virtual Joint *getJoint(); 

        private:
          Part *m_body[3];
      };

    }
  }
}

#endif
