//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Compound.hpp"

using namespace Polycode;

namespace Synthetics {
  namespace Unit {
    Compound::Compound(int noFaces) : Entity(noFaces) {
      m_orientations.resize(noFaces, Vector3(0, 0, 0));
    }

    Compound::~Compound() {
    }

    void Compound::addPlug(int face, Orientation orientation, void *plug) {
      m_orientations.at(face) = orientation;
      m_plugToFace[plug] = face;
    }

    Orientation Compound::getOrientation(int face) {
      return m_orientations.at(face);
    }

    int Compound::getFace(void *plug) {
      return m_plugToFace[plug];
    }
  }
}

