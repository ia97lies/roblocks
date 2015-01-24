//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_COMPOUND_H
#define SYNTHETICS_COMPOUND_H

#include <vector>
#include <string>
#include "PolyVector3.h"

#include "Tag.hpp"

namespace Synthetics {

  class IterateMethod;

  class Compound {
    public:
      Compound();
      virtual ~Compound();

      virtual std::string getName();
      virtual int size();
      virtual int getNoEntries();
      virtual void add(Compound *compound);
      virtual void add(int i, Compound *compound); 
      virtual void remove(int i);
      virtual void remove(Compound *compound);
      virtual Compound *get(int i);
      virtual void iterate(IterateMethod *method);
      virtual std::vector<Compound *> getParents(Compound *compound); 
      virtual void setTag(Tag *tag);
      virtual Tag *getTag();

    private:
      int m_elements;
      std::vector<Compound *> m_compounds;
      bool m_visited;
      Tag *m_tag;

      void iterateRecursive(Compound *parent, IterateMethod *method);
  };

  class IterateMethod {
    public:
      virtual ~IterateMethod() {}
      virtual void call(Compound *parent, Compound *compound) = 0;
  };
 
}

#endif
