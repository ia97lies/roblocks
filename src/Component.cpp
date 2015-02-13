//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Component.hpp"

using namespace Polycode;

namespace Synthetics {
  Component::Component() {
    m_input = Vector3(0, 0, 0);
    m_output = Vector3(0, 0, 0);
  }
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

  void Component::send() {
    for (int i = 0; i < getNoEntries(); i++) {
      Component *component = dynamic_cast<Component *>(get(i));
      component->update(m_output);
    }
    m_output = m_input;
  }
}

