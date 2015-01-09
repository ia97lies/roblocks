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
      bool inPlace(); 
      void place(Component *component);
      void add(Component *component);
      void add();
      void remove();
      void activate(Polycode::Entity *plugShape); 
      void rotateInPlace();
      Plug *getActivePlug();

      static void constructGraphic(PolycodeFacade *facade, Part *parent, Component *component);
      static void destructGraphic(PolycodeFacade *facade, Part *parent, Component *component); 

    private:
      PolycodeFacade *m_polycodeFacade;
      Component *m_mother;
      Component *m_inPlace;

      Component *m_activeComponent;
      Plug *m_activePlug;
      Part *m_activePart;

      Plug *m_inPlacePlug;
      Part *m_inPlacePart;

      Polycode::Vector3 m_rotation;
  };
}

#endif
