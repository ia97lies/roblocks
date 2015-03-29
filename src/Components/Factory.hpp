//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_COMPONENTS_FACTORY_H
#define SYNTHETICS_COMPONENTS_FACTORY_H

#include <string>
#include <map>
#include "PolyPhysicsScene.h"
#include "Component.hpp"

namespace Synthetics {
  namespace Components {

    // NOTE: We need the core for getting time elapsed on send/update cycle
    typedef Component *(*ComponentCreateFn)(Polycode::PhysicsScene *scene);

    class Factory {
      public:
        ~Factory();

        void addCreator(const std::string name, ComponentCreateFn creator);
        Component *createComponent(const std::string name, Polycode::PhysicsScene *scene);
        std::vector<std::string> getNames(); 

        static Factory *get() {
          static Factory instance;
          return &instance; 
        }

      private:
        std::map<std::string, ComponentCreateFn> m_map;
        std::vector<std::string> m_names;

        Factory();
    };

  }
}

#endif
