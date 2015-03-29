//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_ROBOT_H
#define SYNTHETICS_CONSTRUCTOR_ROBOT_H

#include "Polycode.h"
#include "Polycode3DPhysics.h"
#include "PolycodeFacade.hpp"
#include "Compound.hpp"
#include "CompoundStore.hpp"
#include "Component.hpp"

namespace Synthetics {
  namespace Constructor {
    class Robot: public Compound {
      public:
        Robot(PolycodeFacade *facade); 
        virtual ~Robot();

        void powerOn(bool on); 

        void setRoot(Component *component);
        void place(Component *component);
        void rotateInPlace(int direction);
        void add();
        Component *remove();
        void replace(Component *component);

        void activate(Polycode::Entity *plugShape); 
        void deactivate(); 
        void mouseMove(Polycode::Vector3 delta);

        Plug *getActivePlug();
        Knob *getActiveKnob();
        Component *getInPlace();
        Component *getActiveComponent();

        bool isEmpty(); 
        bool isPowerOn(); 

        void update();

        static void constructGraphic(PolycodeFacade *facade, Part *parent, Component *component);
        static void constructPlugsGraphic(PolycodeFacade *facade, Part *curPart); 
        static void constructKnobGraphic(PolycodeFacade *facade, Part *curPart); 
        static void destructGraphic(PolycodeFacade *facade, Component *component); 

      private:
        bool m_powerOn;
        long m_curId;
        PolycodeFacade *m_polycodeFacade;
        Component *m_root;
        Component *m_inPlace;

        CompoundStore *m_components;

        Component *m_activeComponent;
        Plug *m_activePlug;
        Part *m_activePart;
        Knob *m_activeKnob;

        Plug *m_inPlacePlug;
        Part *m_inPlacePart;
    };
  }
}

#endif