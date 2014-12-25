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
    namespace Actor {

      class Servo : public Block {
        public:
          Servo(Polycode::CollisionScene *scene);
          virtual ~Servo();

          virtual void init();
          virtual BlockPlugging *getPlugging();
          virtual Polycode::ScenePrimitive * getShape(); 
          
        private:
          Polycode::CollisionScene *m_scene;
          BlockPlugging *m_plugging;
          Polycode::Color m_color;
          Polycode::ScenePrimitive * m_shape;
      };

    }
  }
}

#endif
