//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Component.hpp"

namespace Synthetics {
  Component::Component() {}
  Component::~Component() {}

  Part *Component::getPartByPlug(Polycode::Entity *plugShape) {
    Part *found = NULL;
    for (int i = 0; !found && i < getNoParts(); i++) {
      Part *part = getPart(i);
      if (part->getPlug(plugShape)) {
        found = part;
      }
    }
    return found;
  }

  Part *Component::getPart(int i) {
  }

  void Component::enable(bool on) {
  }
}

