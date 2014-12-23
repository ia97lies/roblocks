//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolyVector3.h"
#include "Compound.hpp"

namespace Synthetics {
  Compound::Compound() {};
  Compound::~Compound() {};

  int Compound::getNoEntries() {
    return m_compounds.size();
  }

  void Compound::add(Compound *compound) {
    m_compounds.push_back(compound);
  }

  void Compound::remove(int i) {
  }

  Compound *Compound::get(int i) {
    return m_compounds.at(i);
  }
}

