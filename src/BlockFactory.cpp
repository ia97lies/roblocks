//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"

#include "BlockFactory.hpp"

namespace Synthetics {

  BlockFactory::BlockFactory() {
  }

  BlockFactory::~BlockFactory() {
    m_map.clear();
  } 

  void BlockFactory::addCreator(const std::string name, BlockCreateFn creator) {
    m_map[name] = creator;
  }

  Block *BlockFactory::createBlock(const std::string name, Polycode::CollisionScene *scene) {
    std::map<std::string, BlockCreateFn>::iterator it = m_map.find(name);
    if (it != m_map.end()) {
      return it->second(scene);
    }
    return NULL;
  }
}

