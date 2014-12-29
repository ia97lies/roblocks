//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_ROBOT_H
#define SYNTHETICS_ROBOT_H

#include "Polycode.h"
#include "Polycode3DPhysics.h"
#include "PolycodeFacade.hpp"
#include "Compound.hpp"
#include "Component.hpp"

namespace Synthetics {
  class Robot: public Compound {
    public:
      Robot(PolycodeFacade *facade); 
      virtual ~Robot();

      void add(Component *component);
      void remove();
      void activate(Polycode::Entity *plug); 

    private:
      PolycodeFacade *m_polycodeFacade;
      Component *m_mother;
      Component *m_active;
  };
}

#endif
