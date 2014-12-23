//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolyVector3.h"
#include "Compound.hpp"

namespace Synthetics {
  Compound::Compound() {m_elements = 0;};
  Compound::~Compound() {};

  int Compound::size() {
    return m_compounds.size();
  }

  int Compound::getNoEntries() {
    return m_elements;
  }

  void Compound::add(Compound *compound) {
    m_elements++;
    m_compounds.push_back(compound);
  }

  void Compound::add(int i, Compound *compound) {
    if (!m_compounds.at(i)) {
      m_elements++;
    }
    m_compounds.at(i) = compound;
  }

  void Compound::remove(int i) {
    if (m_compounds.at(i)) {
      m_elements--;
    }
    m_compounds.at(i) = NULL;
  }

  Compound *Compound::get(int i) {
    return m_compounds.at(i);
  }
}

