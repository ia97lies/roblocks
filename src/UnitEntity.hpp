//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_UNIT_ENTITY_H
#define SYNTHETICS_UNIT_ENTITY_H

#include "Unit.hpp"

namespace Synthetics {

  class UnitEntity {
    public:
      UnitEntity(int noFaces);
      ~UnitEntity();

      void setActiveFace(int face);
      void addUnit(Unit *unit);
      Unit *getUnit(int face);
      int getNoChilds(); 

    private:
      int m_noFaces;
      int m_activeFace;
      std::vector<Unit *> m_childs;
  };
}

#endif
