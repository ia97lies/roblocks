//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_BLOCK_COMPOUND_H
#define SYNTHETICS_BLOCK_COMPOUND_H

#include <Polycode.h>
#include "Polycode3DPhysics.h"
#include "Block.hpp"
#include "Unit/Compound.hpp"

namespace Synthetics {
  class BlockCompound {
    public:
      BlockCompound(Polycode::CollisionScene *scene, Block *block, int noFaces);
      ~BlockCompound();

      void addOrientation(int face, Polycode::Vector3 position);
      Polycode::Vector3 getOrientation(int face);

      void setActive(bool on); 
      void setActiveFace(int face);
      void setActiveFace(Polycode::Entity *marker); 
      int getActiveFace();
      int getNoChilds();

    private:
      Unit::Compound *m_compound;
  };
}

#endif
