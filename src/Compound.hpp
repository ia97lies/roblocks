//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_COMPOUND_H
#define SYNTHETICS_COMPOUND_H

#include <vector>
#include "PolyVector3.h"

namespace Synthetics {
  class Compound {
    public:
      Compound();
      virtual ~Compound();

      virtual int getNoEntries();
      virtual void add(Compound *compound);
      virtual void remove(int i);
      virtual Compound *get(int i);

    private:
      std::vector<Compound *> m_compounds;
  };
}

#endif
