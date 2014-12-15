//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Entity.hpp"

namespace Synthetics {
  namespace Unit {
    Entity::Entity(int noFaces) {
      m_noFaces = noFaces;
      m_activeFace = 0;
      m_childs.resize(noFaces);
      m_notify = NULL;
    }

    Entity::~Entity() {
      for (int i = 0; i < m_noFaces; i++) {
        Entity *cur = m_childs[i];
        if (cur) {
          cur->remove(this);
        }
      } 
    }

    void Entity::setUserData(void *data, EntityNotifyFn notify) {
      m_userData = data;
      m_notify = notify;
    }

    void *Entity::getUserData() {
      return m_userData; 
    }

    void Entity::setActiveFace(int face) {
      m_childs.at(face);
      m_activeFace = face;
    }

    void Entity::add(Entity *entity) {
      if (entity && !get(m_activeFace)) {
        m_childs[m_activeFace] = entity;
        entity->add(this);
      }
    }

    Entity *Entity::get(int face) {
      return m_childs.at(face);
    }

    Entity *Entity::remove(int face) {
      Entity *ret = m_childs.at(face);
      m_childs.at(face) = NULL;
      ret->notify(m_userData, UNIT_ENTITY_EVENT_REMOVE);
      return ret;
    }

    Entity *Entity::remove(Entity *entity) {
      Entity *found;
      for (int face = 0; face < m_noFaces; face++) {
        if (m_childs[face] == entity) {
          remove(face);
          found = entity;
        }
      }
      return found;
    }

    int Entity::getNoChilds() {
      int no = 0;
      for (int face = 0; face < m_noFaces; face++) {
        no += m_childs[face] ? 1 : 0;
      }
      return no;
    }

    void Entity::notify(void *parentData, int event) {
      if (m_notify) {
        m_notify(m_userData, parentData, event);
      }
    }
  }
}

