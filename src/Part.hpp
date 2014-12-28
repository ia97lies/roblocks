//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_PART_H
#define SYNTHETICS_PART_H

#include "PolyEntity.h"
#include "Plug.hpp"
#include "Compound.hpp"

namespace Synthetics {
  class __attribute__((visibility("default"))) Part : public Compound {
    public:
      Part();
      virtual ~Part();

      virtual Polycode::Entity *getShape() = 0;
      
      int getNoPlugs();
      void addPlug(Plug *plug);
      Plug *getPlug(int i);
      Plug *getPlug(Polycode::Entity *plugShape);

    private:
      std::vector<Plug *> m_plugs;
  };
}

#endif
