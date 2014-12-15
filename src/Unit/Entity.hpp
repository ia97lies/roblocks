//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_UNIT_ENTITY_H
#define SYNTHETICS_UNIT_ENTITY_H

#include <cstddef>
#include <vector>

namespace Synthetics {
  namespace Unit {

    const int UNIT_ENTITY_EVENT_REMOVE = 1;
    typedef void (*EntityNotifyFn)(void *data, void *parentData, int event);

    class Entity {
      public:
        Entity(int noFaces);
        ~Entity();

        void setUserData(void *data, EntityNotifyFn noitfy);
        void *getUserData();
        void setActiveFace(int face);
        void add(Entity *unit);
        Entity *remove(int face);
        Entity *remove(Entity *entity); 
        Entity *get(int face);
        int getNoChilds(); 

      protected:
        void notify(void *parentData, int event);

      private:
        int m_noFaces;
        int m_activeFace;
        std::vector<Entity *> m_childs;
        void *m_userData;
        EntityNotifyFn m_notify;
    };
  }
}

#endif
