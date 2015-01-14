//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include <stdio.h>
#include "PolyVector3.h"
#include "Compound.hpp"

namespace Synthetics {
  Compound::Compound() { 
    m_elements = 0; 
    m_visited = false;
  }

  Compound::~Compound() {}

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
      m_compounds.erase(m_compounds.begin() + i);
    }
  }

  void Compound::remove(Compound *compound) {
    for (int i = 0; getNoEntries(); i++) {
      if (m_compounds.at(i) == compound) {
        remove(i);
      }
    }
  }

  Compound *Compound::get(int i) {
    return m_compounds.at(i);
  }

  void Compound::iterate(IterateMethod *method) {
    if (m_visited) {
      return;
    }
    else for (int i = 0; i < getNoEntries(); i++) {
      m_visited = true;
      get(i)->iterate(method);
      m_visited = false;
    }
    method->call(this);
  }

  class CollectParents : public IterateMethod {
    public:
      CollectParents(Compound *compound) { 
        m_compound = compound;
      }

      virtual ~CollectParents() {}

      virtual void call(Compound *compound) {
        for (int i = 0; i < compound->getNoEntries(); i++) {
          if (m_compound == compound->get(i)) {
            m_parents.push_back(compound);
            break;
          }
        }
      }

      std::vector<Compound *> getParents() {
        return m_parents;
      }

    private:
      Compound *m_compound;
      std::vector<Compound *> m_parents;
  };

  std::vector<Compound *> Compound::getParents(Compound *compound) {
    std::vector<Compound *> parents;
    CollectParents *collector = new CollectParents(compound);
    iterate(collector);
    parents = collector->getParents();
    delete collector;
    return parents;
  }
}

