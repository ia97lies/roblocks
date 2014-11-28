//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include <Polycode.h>
#include "PolycodeView.h"

#include "UnitFactory.hpp"

namespace Synthetics {

  UnitFactory::UnitFactory() {
  }

  UnitFactory::~UnitFactory() {
    m_map.clear();
  } 

  void UnitFactory::addCreator(const std::string name, UnitCreateFn creator) {
    m_map[name] = creator;
  }

  Unit *UnitFactory::createUnit(const std::string name, ::Polycode::Core *core, ::Polycode::Scene *scene) {
    std::map<std::string, UnitCreateFn>::iterator it = m_map.find(name);
    if (it != m_map.end()) {
      return it->second(core, scene);
    }
    return NULL;
  }
}

