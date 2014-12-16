//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_FACTORY_H
#define SYNTHETICS_FACTORY_H

#include <Polycode.h>
#include "PolycodeView.h"

#include "Block.hpp"

namespace Synthetics {

  class BlockFactory {
    public:
      ~BlockFactory();
      
      void addCreator(const std::string name, BlockCreateFn creator);
      Block *createBlock(const std::string name, ::Polycode::CollisionScene *scene);

      static BlockFactory *get() {
        static BlockFactory instance;
        return &instance; 
      }

    private:
      std::map<std::string, BlockCreateFn> m_map;

      BlockFactory();
  };

}

#endif
