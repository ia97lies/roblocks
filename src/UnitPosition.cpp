//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
#include <stdio.h>
#include "UnitPosition.hpp"

using namespace Polycode;

namespace Synthetics {
  UnitPosition::UnitPosition(Vector3 orientation) {
    m_orientation = orientation;
  }

  UnitPosition::~UnitPosition() {}

  Polycode::Vector3 UnitPosition::getOrientation() { 
    return m_orientation; 
  }

  Polycode::Vector3 UnitPosition::getRotation(UnitPosition *pos) { 
    Vector3 o1 = getOrientation();
    Vector3 o2 = pos->getOrientation();
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
}

