//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "CompoundStore.hpp"

namespace Synthetics {
  CompoundStore::CompoundStore() {
    m_curId = 0;
  }

  CompoundStore::~CompoundStore() {
  }

  void CompoundStore::insert(Compound *compound) {
    compound->setId(m_curId);
    store[compound->getId()] = compound;
    ++m_curId;
  }

  Compound *CompoundStore::get(long id) {
    return store[id];
  }
}

