//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_UNIT_COMPONENT_H
#define SYNTHETICS_UNIT_COMPONENT_H

#include <map>
#include "Orientation.hpp"
#include "Entity.hpp"

namespace Synthetics {
  namespace Unit {

    class Compound : Entity {
      public:
        Compound(int noFaces);
        ~Compound();

        void addPlug(int face, Orientation orientation, void *plug);
        Orientation getOrientation(int face);
        int getFace(void *plug);

      protected:
        typedef ::Synthetics::Unit::Entity super;

      private:
        std::vector<Orientation > m_orientations;
        std::map<void *, int> m_plugToFace;
    };
  }
}

#endif
