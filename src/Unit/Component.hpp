//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_UNIT_COMPONENT_H
#define SYNTHETICS_UNIT_COMPONENT_H

#include "Orientation.hpp"
#include "Entity.hpp"

namespace Synthetics {
  namespace Unit {

    class Component : Entity {
      public:
        Component(int noFaces);
        ~Component();

        void addPlug(int face, Orientation orientation, void *plug);
        Orientation getOrientation(int face);

      private:
        std::vector<Orientation > m_orientations;
    };
  }
}

#endif
