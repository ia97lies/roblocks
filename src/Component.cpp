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
    for (int i = 0; i < getNoParts(); i++) {
      Part *part = getPart(i);
      for (int j = 0; j < part->getNoPlugs(); j++) {
        Plug *plug = part->getPlug(j);
        if (plug->isOutput()) {
          Plug *connectedPlug = plug->getConnectedPlug();
          if (connectedPlug && connectedPlug->isInput()) {
            Component *component = dynamic_cast<Component *>(connectedPlug->getParent());
            if (component) {
              component->update(m_output);
            }
          }
        }
      }
    }
    m_output = m_input;
  }
}

