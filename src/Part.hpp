//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_PART_H
#define SYNTHETICS_PART_H

#include "PolyEntity.h"
#include "PolyPhysicsScene.h"
#include "Plug.hpp"
#include "Knob.hpp"
#include "Compound.hpp"

namespace Synthetics {
  class Part : public Compound {
    public:
      Part();
      virtual ~Part();

      virtual Polycode::Entity *getShape() = 0;

      virtual void setMass(float mass);
      virtual float getMass();
      
      int getNoPlugs();
      void addPlug(Plug *plug);
      Plug *getPlug(int i);
      Plug *getPlug(Polycode::Entity *plugShape);
      void plug(Part *part, float factor); 
      void setPhysicsHinge(Polycode::PhysicsHingeConstraint *hinge);
      Polycode::PhysicsHingeConstraint *getPhysicsHinge();
      // TODO: add/remove/get joints

      void setKnob(Knob *knob);
      Knob *getKnob();

    private:
      float m_mass;
      std::vector<Plug *> m_plugs;
      Knob *m_knob;
      Polycode::PhysicsHingeConstraint *m_hinge;
  };
}

#endif
