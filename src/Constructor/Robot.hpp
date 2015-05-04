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
        void add();
        Component *remove();
        void replace(Component *component);

        void activate(Polycode::Entity *shape); 
        void deactivate(Polycode::Entity *shape); 
        void mouseMove(Polycode::Vector3 delta);

        void setActive(Component *component, Part *part, Plug *plug); 
        void setActiveKnob(Knob *knob);
        Plug *getActivePlug();
        Knob *getActiveKnob();
        Part *getActivePart();
        Component *getActiveComponent();

        void setInPlace(Component *component, Part *part, Plug *plug);
        Plug *getInPlacePlug();
        Component *getInPlace();
        Part *getInPlacePart();

        bool isEmpty(); 
        bool isPowerOn(); 

        void update(Number dt);

        static void constructGraphic(PolycodeFacade *facade, Part *parent, Component *component);
        static void constructPlugsGraphic(PolycodeFacade *facade, Part *curPart); 
        static void constructKnobGraphic(PolycodeFacade *facade, Part *curPart); 
        static void destructPlugsGraphic(PolycodeFacade *facade, Part *curPart); 
        static void destructGraphic(PolycodeFacade *facade, Component *component); 
        static void constructPhysics(PolycodeFacade *facade, Part *parent, Component *component); 
        static void destructPhysics(PolycodeFacade *facade, Component *component); 

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
