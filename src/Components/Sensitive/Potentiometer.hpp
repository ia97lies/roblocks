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

          virtual void updateNg();

        private:
          Part *m_body[2];
      };

    }
  }
}

#endif
