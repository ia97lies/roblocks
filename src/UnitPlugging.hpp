//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_UNIT_PLUGGING_H
#define SYNTHETICS_UNIT_PLUGGING_H

#include <Polycode.h>
#include "PolycodeView.h"

#include "PolycodeUnit.hpp"

namespace Synthetics {

  class UnitPlugging {
    public:
          UnitPlugging(Polycode::CollisionScene *scene, PolycodeUnit *unit, int noFaces);
          ~UnitPlugging();

          int getNoFaces();

          void addOrientation(int face, Polycode::Vector3 position);
          Polycode::Vector3 getOrientation(int face);
          
          void setActive(bool on); 
          bool setActiveFace(int face);
          bool setActiveFace(Polycode::Entity *marker); 
          int getActiveFace();
          int getNoChilds();

          bool addUnit(PolycodeUnit *unit);
          void linkUnit(PolycodeUnit *unit);
          void removeUnit(PolycodeUnit *unit);
          PolycodeUnit *getUnit(int face);

    private:
          std::vector<Polycode::Vector3> m_orientations;
          std::vector<PolycodeUnit *> m_childs;
          std::vector<Polycode::ScenePrimitive *> m_connectors;
          Polycode::CollisionScene *m_scene;
          PolycodeUnit *m_unit; 
          int m_noFaces;
          Polycode::Color m_connectorColor;
          Polycode::Color m_markerColor;
          int m_activeFace;
  };
}

#endif
