//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_PASSIVE_HUB_H
#define SYNTHETICS_PASSIVE_HUB_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Block.hpp"

namespace Synthetics {
  namespace Blocks {
    namespace Passive {

      class Hub : public Block {
        public:
          Hub(Polycode::CollisionScene *scene);
          virtual ~Hub();

          virtual void init();
          virtual BlockPlugging *getPlugging();
          virtual Polycode::ScenePrimitive * getPolycodeObject(); 
          virtual void handleEvent(Unit::Event *event);
          
        private:
          Polycode::CollisionScene *m_scene;
          BlockPlugging *m_plugging;
          Polycode::Color m_color;
          Polycode::ScenePrimitive * m_shape;

          float clamp(float value, float min, float max);
      };

    }
  }
}

#endif
