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
  UnitEntity::~UnitEntity() {}

  void UnitEntity::setActiveFace(int face) {
    m_childs.at(face);
    m_activeFace = face;
  }

  void UnitEntity::addUnit(Unit *unit) {
    m_childs[m_activeFace] = unit;
  }

  Unit *UnitEntity::getUnit(int face) {
    return m_childs.at(face);
  }

  int UnitEntity::getNoChilds() {
    int no = 0;
    for (int face = 0; face < m_noFaces; face++) {
      no += m_childs[face] ? 1 : 0;
    }
    return no;
  }
}

