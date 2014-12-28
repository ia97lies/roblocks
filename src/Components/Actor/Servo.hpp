//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_COMPONENTS_ACTOR_SERVO_H
#define SYNTHETICS_COMPONENTS_ACTOR_SERVO_H

#include "Part.hpp"
#include "Component.hpp"

namespace Synthetics {
  namespace Components {
    namespace Actor {

      class Servo : public Component {
        public:
          Servo();
          virtual ~Servo();

          virtual int getNoParts();
          virtual Part *getPart(int i);

        private:
          Part *m_body[2];
      };

    }
  }
}

#endif
