//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_UNIT_ENTITY_H
#define SYNTHETICS_UNIT_ENTITY_H

#include <cstddef>
#include <vector>

namespace Synthetics {

  class UnitEntity {
    public:
      UnitEntity(int noFaces);
      ~UnitEntity();

      void setUserData(void *data);
      void *getUserData();
      void setActiveFace(int face);
      void add(UnitEntity *unit);
      UnitEntity *remove(int face);
      UnitEntity *remove(UnitEntity *entity); 
      UnitEntity *get(int face);
      int getNoChilds(); 

    private:
      int m_noFaces;
      int m_activeFace;
      std::vector<UnitEntity *> m_childs;
      void *m_userData;
  };
}

#endif
