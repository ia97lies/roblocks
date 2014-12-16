//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_FACTORY_H
#define SYNTHETICS_FACTORY_H

#include <Polycode.h>
#include "PolycodeView.h"

#include "PolycodeUnit.hpp"

namespace Synthetics {

  class UnitFactory {
    public:
      ~UnitFactory();
      
      void addCreator(const std::string name, UnitCreateFn creator);
      PolycodeUnit *createUnit(const std::string name, ::Polycode::Core *core, ::Polycode::CollisionScene *scene);

      static UnitFactory *get() {
        static UnitFactory instance;
        return &instance; 
      }

    private:
      std::map<std::string, UnitCreateFn> m_map;

      UnitFactory();
  };

}

#endif
