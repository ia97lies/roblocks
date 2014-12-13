//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "UnitEntity.hpp"

namespace Synthetics {
  UnitEntity::UnitEntity(int noFaces) {
    m_noFaces = noFaces;
    m_activeFace = 0;
    m_childs.resize(noFaces);
    m_notify = NULL;
  }

  UnitEntity::~UnitEntity() {
    for (int i = 0; i < m_noFaces; i++) {
      UnitEntity *cur = m_childs[i];
      if (cur) {
        cur->remove(this);
      }
    } 
  }

  void UnitEntity::setUserData(void *data, UnitEntityNotifyFn notify) {
    m_userData = data;
    m_notify = notify;
  }

  void *UnitEntity::getUserData() {
    return m_userData; 
  }

  void UnitEntity::setActiveFace(int face) {
    m_childs.at(face);
    m_activeFace = face;
  }

  void UnitEntity::add(UnitEntity *entity) {
    if (entity && !get(m_activeFace)) {
      m_childs[m_activeFace] = entity;
      entity->add(this);
    }
  }

  UnitEntity *UnitEntity::get(int face) {
    return m_childs.at(face);
  }

  UnitEntity *UnitEntity::remove(int face) {
    UnitEntity *ret = m_childs.at(face);
    m_childs.at(face) = NULL;
    ret->notify(m_userData, UNIT_ENTITY_EVENT_REMOVE);
    return ret;
  }

  UnitEntity *UnitEntity::remove(UnitEntity *entity) {
    UnitEntity *found;
    for (int face = 0; face < m_noFaces; face++) {
      if (m_childs[face] == entity) {
        remove(face);
        found = entity;
      }
    }
    return found;
  }

  int UnitEntity::getNoChilds() {
    int no = 0;
    for (int face = 0; face < m_noFaces; face++) {
      no += m_childs[face] ? 1 : 0;
    }
    return no;
  }

  void UnitEntity::notify(void *parentData, int event) {
    if (m_notify) {
      m_notify(m_userData, parentData, event);
    }
  }
}

