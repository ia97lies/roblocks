//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_COMPOUNDS_FACTORY_H
#define SYNTHETICS_COMPOUNDS_FACTORY_H

#include <string>
#include <map>
#include "Compound.hpp"

namespace Synthetics {
  namespace Compounds {

    typedef Compound *(*CompoundCreateFn)();

    class Factory {
      public:
        ~Factory();

        void addCreator(const std::string name, CompoundCreateFn creator);
        Compound *createCompound(const std::string name);

        static Factory *get() {
          static Factory instance;
          return &instance; 
        }

      private:
        std::map<std::string, CompoundCreateFn> m_map;

        Factory();
    };

  }
}

#endif
