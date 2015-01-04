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

      bool isEmpty(); 
      void add(Component *component);
      void remove();
      void activate(Polycode::Entity *plugShape); 
      Plug *getActivePlug(); 

      static void constructGraphic(PolycodeFacade *facade, Part *parent, Component *component);
      static void destructGraphic(PolycodeFacade *facade, Part *parent, Component *component); 

    private:
      PolycodeFacade *m_polycodeFacade;
      Component *m_mother;
      Plug *m_activePlug;
      Part *m_activePart;
      Component *m_active;

      void activate(Component *parent, Polycode::Entity *plugShape); 
  };
}

#endif
