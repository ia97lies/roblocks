//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolyScenePrimitive.h"
#include "PolySceneLabel.h"
#include "Plug.hpp"

using namespace Polycode;

namespace Synthetics {
  Plug::Plug(Polycode::Vector3 position, Polycode::Vector3 rotation) {
    m_position = position;
    m_rotation = rotation;
    m_shape = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.2, 0.8, 0.8);
    m_shape->setColor(1, 0, 0, 0.5);
  }

  Plug::~Plug() {
    delete m_shape;
  };

  Vector3 Plug::getPosition() {
    return m_position; 
  }

  Vector3 Plug::getRotation() {
    return m_rotation; 
  }

  Vector3 Plug::getFaceToFaceRotation(Plug *plug) { 
    Vector3 o1 = getPosition();
    o1.Normalize();
    Vector3 o2 = plug->getPosition();
    o2.Normalize();
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
    Vector3 rotation = axis * round(angle * (-1) * 180 / PI);
    return rotation;
  }

  Polycode::Entity *Plug::getShape() {
    return m_shape;
  }

  void Plug::activate(bool on) {
    m_on = on;
    if (m_on) {
      m_shape->setColor(1, 0, 0, 1);
    }
    else {
      m_shape->setColor(1, 0, 0, 0.5);
    }
  }

  bool Plug::isActivate() {
    return m_on;
  }

}

