//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_COMPOUNDSTORE_H
#define SYNTHETICS_COMPOUNDSTORE_H

#include <map>
#include "Compound.hpp"

namespace Synthetics {

  class CompoundStore {
    public:
      CompoundStore();
      virtual ~CompoundStore();

      virtual void insert(Compound *compound);
      virtual void insert(long id, Compound *compound);
      virtual void remove(long id);
      virtual Compound *get(long id);
      virtual std::map<long, Compound*> getMap();

    private:
      long m_curId;
      std::map<long, Compound*> store;
  };
}

#endif
