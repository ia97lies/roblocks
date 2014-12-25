//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Factory.hpp"

namespace Synthetics {
  namespace Components {

    Factory::Factory() {
    }

    Factory::~Factory() {
      m_map.clear();
    } 

    void Factory::addCreator(const std::string name, ComponentCreateFn creator) {
      m_map[name] = creator;
    }

    Component *Factory::createComponent(const std::string name) {
      std::map<std::string, ComponentCreateFn>::iterator it = m_map.find(name);
      if (it != m_map.end()) {
        return it->second();
      }
      return NULL;
    }

  }
}

