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
      if (m_map[name] == NULL) {
        m_names.push_back(name);
      }
      m_map[name] = creator;
    }

    Component *Factory::createComponent(const std::string name, Polycode::Core *core, Polycode::Scene *scene) {
      std::map<std::string, ComponentCreateFn>::iterator it = m_map.find(name);
      if (it != m_map.end()) {
        return it->second(core, scene);
      }
      return NULL;
    }

    std::vector<std::string> Factory::getNames() {
      return m_names;
    }
  }
}

