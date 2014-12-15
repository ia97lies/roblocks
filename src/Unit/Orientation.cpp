//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
#include <stdio.h>
#include "Orientation.hpp"

using namespace Polycode;

namespace Synthetics {
  namespace Unit {
    Orientation::Orientation(Vector3 orientation) {
      m_orientation = orientation;
    }

    Orientation::~Orientation() {}

    Polycode::Vector3 Orientation::get() { 
      return m_orientation; 
    }

    Polycode::Vector3 Orientation::getRotation(Orientation *orientation) { 
      Vector3 o1 = get();
      Vector3 o2 = orientation->get();
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
}

