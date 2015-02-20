//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Component.hpp"

using namespace Polycode;

namespace Synthetics {
  Component::Component() {
    m_output = 0;
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


  Polycode::Vector3 Component::getOutput() {
    return m_output;
  }

  void Component::updateNg() {
    Vector3 value = 0;

    // get connected plugs value depending what kind of plugs are connected 
    // together
    for (int i = 0; i < getNoParts(); i++) {
      Part *part = getPart(i);
      for (int j = 0; j < part->getNoPlugs(); j++) {
        Plug *plug = part->getPlug(j);
        Plug *connectedPlug = plug->getConnectedPlug();
        if (connectedPlug && plug->isInOut() && connectedPlug->isOutput()) {
          plug->setValue(connectedPlug->getValue());
          value += connectedPlug->getValue();
        }
        else if (connectedPlug && plug->isInput() && connectedPlug->isOutput()) {
          plug->setValue(connectedPlug->getValue());
          value += connectedPlug->getValue();
        }
        else if (connectedPlug && plug->isInput() && connectedPlug->isInOut()) {
          plug->setValue(connectedPlug->getValue());
          value += connectedPlug->getValue();
        }
        else if (connectedPlug && plug->isInOut() && connectedPlug->isInOut()) {
          plug->setValue(connectedPlug->getValue());
          value += connectedPlug->getValue();
        }
      }
    }

    m_output = value;

    // set collected value to my plugs
    for (int i = 0; i < getNoParts(); i++) {
      Part *part = getPart(i);
      for (int j = 0; j < part->getNoPlugs(); j++) {
        Plug *plug = part->getPlug(j);
        Plug *connectedPlug = plug->getConnectedPlug();
        if (connectedPlug && plug->isInOut() && connectedPlug->isInOut()) {
          plug->setValue(value - connectedPlug->getValue());
        }
        else {
          plug->setValue(value);
        }
      }
    }
  }
}

