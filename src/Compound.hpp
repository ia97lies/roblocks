//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_COMPOUND_H
#define SYNTHETICS_COMPOUND_H

#include <vector>
#include "PolyVector3.h"

namespace Synthetics {

  class IterateMethod;

  class Compound {
    public:
      Compound();
      virtual ~Compound();

      virtual int size();
      virtual int getNoEntries();
      virtual void add(Compound *compound);
      virtual void add(int i, Compound *compound); 
      virtual void remove(int i);
      virtual Compound *get(int i);
      virtual void iterate(IterateMethod *method);
      virtual std::vector<Compound *> getParents(Compound *compound); 

    private:
      int m_elements;
      std::vector<Compound *> m_compounds;
      bool m_visited;
  };

  class IterateMethod {
    public:
      virtual ~IterateMethod() {}
      virtual void call(Compound *compound) = 0;
  };
 
}

#endif
