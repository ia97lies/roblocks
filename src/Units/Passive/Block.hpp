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
          Block(Polycode::Core *core, Polycode::CollisionScene *scene);
          virtual ~Block();

          virtual int noFaces();
          virtual bool setActiveFace(int face);
          virtual bool setActiveFace(Polycode::Entity *marker); 
          virtual bool addUnit(Unit *unit);
          virtual void linkUnit(Unit *unit);
          virtual void removeUnit(Unit *unit);
          virtual Unit *getUnit(int face);
          virtual void setActive(bool on);
          virtual int getActiveFace();
          virtual int noChilds();

          virtual Polycode::Vector3 getOrientation(int face);
          virtual Polycode::ScenePrimitive * getPolycodeObject(); 
          virtual void handleEvent(Polycode::Event *event);
          
        private:
          static const int s_noFaces = 6;
          Polycode::Core *m_core;
          Polycode::CollisionScene *m_scene;
          Polycode::Vector3 m_faces[s_noFaces];
          Unit *m_childs[s_noFaces];
          Polycode::ScenePrimitive *m_connectors[s_noFaces];
          int m_activeFace;
          Polycode::Vector3 m_shapeColor;
          Polycode::Vector3 m_connectorColor;
          Polycode::Vector3 m_markerColor;

          Polycode::ScenePrimitive * m_shape;

          float clamp(float value, float min, float max);
      };

    }
  }
}

#endif
