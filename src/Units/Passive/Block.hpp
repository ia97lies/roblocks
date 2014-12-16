//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_PASSIVE_BLOCK_H
#define SYNTHETICS_PASSIVE_BLOCK_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "PolycodeUnit.hpp"

namespace Synthetics {
  namespace Units {
    namespace Passive {

      class Block : public PolycodeUnit {
        public:
          Block(Polycode::Core *core, Polycode::CollisionScene *scene);
          virtual ~Block();

          virtual void init();
          virtual UnitPlugging *getPlugging();
          virtual void setActive(bool on);
          virtual Polycode::ScenePrimitive * getPolycodeObject(); 
          virtual void handleEvent(Unit::Event *event);
          
        private:
          Polycode::Core *m_core;
          Polycode::CollisionScene *m_scene;
          UnitPlugging *m_plugging;
          Polycode::Color m_color;
          Polycode::ScenePrimitive * m_shape;

          float clamp(float value, float min, float max);
      };

    }
  }
}

#endif
