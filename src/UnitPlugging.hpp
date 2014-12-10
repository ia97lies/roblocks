//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_UNIT_PLUGGING_H
#define SYNTHETICS_UNIT_PLUGGING_H

#include <Polycode.h>
#include "PolycodeView.h"

#include "Unit.hpp"

namespace Synthetics {

  class UnitPlugging {
    public:
          UnitPlugging(Polycode::Core *core, Polycode::CollisionScene *scene, Unit *unit, int noFaces);
          ~UnitPlugging();

          int getNoFaces();

          void addOrientation(int face, Polycode::Vector3 position);
          Polycode::Vector3 getOrientation(int face);
          
          void setActive(bool on); 
          bool setActiveFace(int face);
          bool setActiveFace(Polycode::Entity *marker); 
          int getActiveFace();
          int getNoChilds();

          bool addUnit(Unit *unit);
          void linkUnit(Unit *unit);
          void removeUnit(Unit *unit);
          Unit *getUnit(int face);

    private:
          std::vector<Polycode::Vector3> m_orientations;
          std::vector<Unit *> m_childs;
          std::vector<Polycode::ScenePrimitive *> m_connectors;
          Polycode::Core *m_core; 
          Polycode::CollisionScene *m_scene;
          Unit *m_unit; 
          int m_noFaces;
          Polycode::Color m_connectorColor;
          Polycode::Color m_markerColor;
          int m_activeFace;
  };
}

#endif
