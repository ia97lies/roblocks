//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_PART_H
#define SYNTHETICS_PART_H

#include "PolyEntity.h"
#include "Plug.hpp"
#include "Knob.hpp"
#include "Compound.hpp"

namespace Synthetics {
  class Part : public Compound {
    public:
      Part();
      virtual ~Part();

      virtual Polycode::Entity *getShape() = 0;
      
      int getNoPlugs();
      void addPlug(Plug *plug);
      Plug *getPlug(int i);
      Plug *getPlug(Polycode::Entity *plugShape);
      void plug(Plug *plug1, Plug *plug2, float factor);

      void setKnob(Knob *knob);
      Knob *getKnob();

    private:
      std::vector<Plug *> m_plugs;
      Knob *m_knob;
  };
}

#endif
