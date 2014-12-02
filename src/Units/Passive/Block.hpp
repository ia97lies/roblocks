//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_PASSIVE_BLOCK_H
#define SYNTHETICS_PASSIVE_BLOCK_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Unit.hpp"

namespace Synthetics {
  namespace Units {
    namespace Passive {

      class Block : public Unit {
        public:
          Block(Polycode::Core *core, Polycode::Scene *scene);
          virtual ~Block();

          virtual int noOfFaces();
          virtual Polycode::Vector3 getOrientation(int face);
          virtual void addUnit(int face, Unit *unit);
          virtual Unit *getUnit(int face);
          virtual void setActive(bool on);
          virtual Polycode::ScenePrimitive * getPolycodeObject(); 
          virtual void handleEvent(Polycode::Event *event);
          
        private:
          static const int s_noOfFaces = 6;
          Polycode::Core *m_core;
          Polycode::Scene *m_scene;
          Polycode::Vector3 m_faces[s_noOfFaces];
          Unit *m_units[s_noOfFaces];

          Polycode::ScenePrimitive * m_shape;
      };

    }
  }
}

#endif
