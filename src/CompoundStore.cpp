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
    insert(compound->getId(), compound);
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

  void CompoundStore::remove(long id) {
    store.erase(id);
  }

  Compound *CompoundStore::get(long id) {
    return store[id];
  }

  std::map<long, Compound*> CompoundStore::getMap() {
    return store;
  }
}

