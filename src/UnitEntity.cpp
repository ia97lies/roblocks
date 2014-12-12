//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "UnitEntity.hpp"

namespace Synthetics {
  UnitEntity::UnitEntity(int noFaces) {
    m_noFaces = noFaces;
    m_activeFace = 0;
    m_childs.resize(noFaces);
  }
  UnitEntity::~UnitEntity() {

  }

  void UnitEntity::setUserData(void *data) {
    m_userData = data;
  }

  void *UnitEntity::getUserData() {
    return m_userData; 
  }

  void UnitEntity::setActiveFace(int face) {
    m_childs.at(face);
    m_activeFace = face;
  }

  void UnitEntity::add(UnitEntity *entity) {
    m_childs[m_activeFace] = entity;
  }

  UnitEntity *UnitEntity::get(int face) {
    return m_childs.at(face);
  }

  UnitEntity *UnitEntity::remove(int face) {
    UnitEntity *ret = m_childs.at(face);
    m_childs.at(face) = NULL;
    return ret;
  }

  UnitEntity *UnitEntity::remove(UnitEntity *entity) {
    UnitEntity *found;
    for (int face = 0; face < m_noFaces; face++) {
      if (m_childs[face] == entity) {
        m_childs[face] = NULL;
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
}

