//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Factory.hpp"

namespace Synthetics {
  namespace Compounds {

    Factory::Factory() {
    }

    Factory::~Factory() {
      m_map.clear();
    } 

    void Factory::addCreator(const std::string name, CompoundCreateFn creator) {
      m_map[name] = creator;
    }

    Compound *Factory::createCompound(const std::string name) {
      std::map<std::string, CompoundCreateFn>::iterator it = m_map.find(name);
      if (it != m_map.end()) {
        return it->second();
      }
      return NULL;
    }

  }
}

