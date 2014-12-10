//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include <Polycode.h>
#include "PolycodeView.h"

#include "Unit.hpp"
#include "UnitPlugging.hpp"

using namespace Polycode;

namespace Synthetics {

  UnitPlugging::UnitPlugging(Polycode::Core *core, CollisionScene *scene, Unit *unit, int noFaces) {
    m_core = core;
    m_scene = scene;
    m_unit = unit;
    m_noFaces = noFaces;
    m_childs.reserve(noFaces);
    m_connectors.reserve(noFaces);
    m_orientations.reserve(noFaces);
    m_connectorColor = Vector3(0.5, 1.0, 0.5);
    m_markerColor = Vector3(0.8, 0.2, 0.2);
    m_activeFace = 0;
    for (int i = 0 ; i < m_noFaces; i++) {
      m_childs[i] = NULL;
      ScenePrimitive *shape = unit->getPolycodeObject();
      m_connectors[i] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.5,0.5,0.5);
      shape->addChild(m_connectors[i]);
      m_connectors[i]->setColor(m_connectorColor.x, m_connectorColor.y, m_connectorColor.z, 0.6);
      m_connectors[i]->setPosition(this->getOrientation(i) * 0.4);
      m_scene->trackCollision(m_connectors[i]);
    }

    this->setActiveFace(0);
  }

  UnitPlugging::~UnitPlugging() {
    for (int i = 0; i < m_noFaces; i++) {
      if (m_childs[i] != NULL) {
        m_childs[i]->removeUnit(m_unit);
      }
    }
    for (int i = 0; i < m_noFaces; i++) {
      m_scene->removeEntity(m_connectors[i]);
      delete m_connectors[i];
    }
  }

  Polycode::ScenePrimitive * UnitPlugging::getPolycodeObject() {
    return m_unit->getPolycodeObject();
  }

  int UnitPlugging::getNoFaces() {
    return m_noFaces;
  }

  void UnitPlugging::addOrientation(int face, Vector3 orientation) {
    m_orientations.at(face) = orientation;
  }

  Polycode::Vector3 UnitPlugging::getOrientation(int face) {
    return m_orientations.at(face);
  }

  void UnitPlugging::setActive(bool on) {
    if (!on) {
      for (int face = 0; face < m_noFaces; face++) {
        m_connectors[face]->setColor(m_connectorColor.x, m_connectorColor.y, m_connectorColor.z, 0.4);
      }
    }
    else {
      for (int face = 0; face < m_noFaces; face++) {
        m_connectors[face]->setColor(m_connectorColor.x, m_connectorColor.y, m_connectorColor.z, 1.0);
      }
    }
  }

  bool UnitPlugging::setActiveFace(int face) {
    bool ok = true;
    if (face >= 0 && face < m_noFaces) {
      m_connectors[m_activeFace]->setColor(m_connectorColor.x, m_connectorColor.y, m_connectorColor.z, 1.0);
      m_activeFace = face;
      m_connectors[m_activeFace]->setColor(m_markerColor.x, m_markerColor.y, m_markerColor.z, 1.0);
    }
    else {
      ok = false;
    }
    return ok;
  }

  bool UnitPlugging::setActiveFace(Polycode::Entity *marker) {
    return false;
  }

  int UnitPlugging::getActiveFace() {
    return m_activeFace;
  }

  int UnitPlugging::getNoChilds() {
    int no = 0;
    for (int face = 0; face < m_noFaces; face++) {
      no += m_childs[face] ? 1 : 0;
    }
    return no;
  }

  bool UnitPlugging::addUnit(Unit *unit) {
    bool ok = true;
    if (m_childs[m_activeFace] == NULL) {
      m_childs[m_activeFace] = unit;
      unit->linkUnit(unit);
      ScenePrimitive *shape = unit->getPolycodeObject();
      ScenePrimitive *selectedShape = m_unit->getPolycodeObject();
      selectedShape->addChild(shape);
      m_scene->trackCollision(shape);
      shape->setPosition(this->getOrientation(m_activeFace));

      Vector3 o1 = this->getOrientation(m_activeFace);
      Vector3 o2 = unit->getOrientation(unit->getActiveFace());
      float angle = acos(o1.dot(o2)) + PI;
      angle = angle < 2*PI ? angle : 0;
      Vector3 axis = o1.crossProduct(o2);
      if (axis.length() == 0) {
        if (o2.x == 0) {
          axis.x = 1;
        }
        else if (o2.y == 0) {
          axis.y = 1;
        }
        else {
          axis.z = 1;
        }
      } 
      Vector3 rotation = axis * (angle * (-1) * 180 / PI);
      shape->setRotationEuler(rotation);
    }
    else {
      ok = false;
    }
    return ok;
  }

  void UnitPlugging::linkUnit(Unit *unit) {
    m_childs[m_activeFace] = unit;
  }

  void UnitPlugging::removeUnit(Unit *unit) {
    for (int face = 0; face < m_noFaces; face++) {
      if (m_childs[face] == unit) {
        ScenePrimitive *shape = m_unit->getPolycodeObject();
        shape->removeChild(unit->getPolycodeObject());
        m_childs[face] = NULL;
      }
    }
  }

  Unit *UnitPlugging::getUnit(int face) {
    return m_childs.at(face);
  }
}

