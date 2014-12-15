//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Component.hpp"

using namespace Polycode;

namespace Synthetics {
  namespace Unit {
    Component::Component(int noFaces) : Entity(noFaces) {
      m_orientations.resize(noFaces, Vector3(0, 0, 0));
    }

    Component::~Component() {
    }

    void Component::addPlug(int face, Orientation orientation, void *plug) {
      m_orientations.at(face) = orientation;
    }

    Orientation Component::getOrientation(int face) {
      return m_orientations.at(face);
    }
  }
}

