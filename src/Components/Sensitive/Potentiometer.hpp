//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_COMPONENTS_SENSITIVIVE_POTENTIOMETER_H
#define SYNTHETICS_COMPONENTS_SENSITIVIVE_POTENTIOMETER_H

#include "Part.hpp"
#include "Component.hpp"

namespace Synthetics {
  namespace Components {
    namespace Sensitive {

      class Potentiometer : public Component {
        public:
          Potentiometer();
          virtual ~Potentiometer();

          virtual std::string getName(); 
          virtual int getNoParts();
          virtual Part *getPart(int i);
          virtual void enable(bool on); 

          virtual void send();
          virtual void update(Polycode::Vector3 delta);

        private:
          Part *m_body[2];
          Polycode::Vector3 m_input;
          Polycode::Vector3 m_output;
      };

    }
  }
}

#endif
