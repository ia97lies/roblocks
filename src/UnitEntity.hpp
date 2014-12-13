//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_UNIT_ENTITY_H
#define SYNTHETICS_UNIT_ENTITY_H

#include <cstddef>
#include <vector>

namespace Synthetics {

  const int UNIT_ENTITY_EVENT_REMOVE = 1;
  typedef void (*UnitEntityNotifyFn)(void *data, void *parentData, int event);

  class UnitEntity {
    public:
      UnitEntity(int noFaces);
      ~UnitEntity();

      void setUserData(void *data, UnitEntityNotifyFn noitfy);
      void *getUserData();
      void setActiveFace(int face);
      void add(UnitEntity *unit);
      UnitEntity *remove(int face);
      UnitEntity *remove(UnitEntity *entity); 
      UnitEntity *get(int face);
      int getNoChilds(); 

    protected:
      void notify(void *parentData, int event);

    private:
      int m_noFaces;
      int m_activeFace;
      std::vector<UnitEntity *> m_childs;
      void *m_userData;
      UnitEntityNotifyFn m_notify;
  };
}

#endif
