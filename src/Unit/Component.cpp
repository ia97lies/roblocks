//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Component.hpp"

namespace Synthetics {
  namespace Unit {
    Component::Component(int noFaces) : Entity(noFaces) {
    }

    Component::~Component() {
    }

    void Component::addPlug(int face, Orientation orientation, void *plug) {
    }
  }
}

