//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_ROBOT_H
#define SYNTHETICS_ROBOT_H

#include "Polycode.h"
#include "Polycode3DPhysics.h"
#include "Compound.hpp"
#include "Component.hpp"

namespace Synthetics {
  class Robot: public Compound {
    public:
      Robot(Polycode::Core *core, Polycode::CollisionScene *scene); 
      virtual ~Robot();

      void add(Component *component);
      void remove();
      void activate(void *plug);
    private:
      Polycode::Core *m_core;
      Polycode::CollisionScene *m_scene;
  };
}

#endif
