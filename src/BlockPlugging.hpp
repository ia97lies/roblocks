//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_BLOCK_PLUGGING_H
#define SYNTHETICS_BLOCK_PLUGGING_H

#include <Polycode.h>
#include "PolycodeView.h"

#include "Block.hpp"

namespace Synthetics {

  class BlockPlugging {
    public:
          BlockPlugging(Polycode::CollisionScene *scene, Block *block, int noFaces);
          ~BlockPlugging();

          int getNoFaces();

          void addOrientation(int face, Polycode::Vector3 position);
          Polycode::Vector3 getOrientation(int face);
          
          void setActive(bool on); 
          bool setActiveFace(int face);
          bool setActiveFace(Polycode::Entity *marker); 
          int getActiveFace();
          int getNoChilds();

          bool addBlock(Block *block);
          void removeBlock(Block *block);
          Block *getBlock(int face);

    private:
          std::vector<Polycode::Vector3> m_orientations;
          std::vector<Block *> m_childs;
          std::vector<Polycode::ScenePrimitive *> m_connectors;
          Polycode::CollisionScene *m_scene;
          Block *m_block; 
          int m_noFaces;
          Polycode::Color m_connectorColor;
          Polycode::Color m_markerColor;
          int m_activeFace;

          void linkBlock(Block *block);
  };
}

#endif
