//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "BlockCompound.hpp"

using namespace Polycode;

namespace Synthetics {
  BlockCompound::BlockCompound(Polycode::CollisionScene *scene, Block *block, int noFaces) {
    m_compound = new Unit::Compound(noFaces);
  }

  BlockCompound::~BlockCompound() {
  }

  void BlockCompound::addOrientation(int face, Polycode::Vector3 position) {
  }

  Polycode::Vector3 BlockCompound::getOrientation(int face) {
    return Vector3(0,0,0);
  }

  void BlockCompound::setActive(bool on) {
  }

  void BlockCompound::setActiveFace(int face) {
    m_compound->setActiveFace(face);
  }

  void BlockCompound::setActiveFace(Polycode::Entity *marker) {
    m_compound->setActiveFace(m_compound->getFace(marker));
  }

  int BlockCompound::getActiveFace() {
    return false;
  }

  int BlockCompound::getNoChilds() {
    return m_compound->getNoChilds();
  }
}

