//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_COMPONENTS_ACTOR_LOUDSPEAKER_H
#define SYNTHETICS_COMPONENTS_ACTOR_LOUDSPEAKER_H

#include "Part.hpp"
#include "Component.hpp"

namespace Synthetics {
  namespace Components {
    namespace Active {

      class Loudspeaker : public Component {
        public:
          Loudspeaker (Polycode::Scene *scene);
          virtual ~Loudspeaker();

          virtual std::string getName(); 
          virtual int getNoParts();
          virtual Part *getPart(int i);
          virtual void enable(bool on); 

        private:
          Polycode::Scene *m_scene;
          Part *m_body;
          Knob *m_knob;
          Polycode::SceneSound *m_sound;
      };

    }
  }
}

#endif
