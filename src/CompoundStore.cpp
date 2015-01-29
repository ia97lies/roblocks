//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Exceptions.hpp"
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

  void CompoundStore::insert(long id, Compound *compound) {
    compound->setId(id);
    if (store[compound->getId()] == NULL) {
      store[compound->getId()] = compound;
    }
    else {
      throw AlreadyExistException();
    }
  }

  Compound *CompoundStore::get(long id) {
    return store[id];
  }
}

