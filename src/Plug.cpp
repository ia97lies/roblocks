//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Plug.hpp"

using namespace Polycode;

namespace Synthetics {
  Plug::Plug(Polycode::Vector3 position, Polycode::Vector3 rotation) {
    m_position = position;
    m_rotation = rotation;
    m_data = NULL;
  }

  Plug::~Plug() {};

  void Plug::setUserData(void *data) {
    m_data = data;
  }

  void *Plug::getUserData() {
    return m_data;
  }

  Vector3 Plug::getPosition() {
    return m_position; 
  }

  Vector3 Plug::getRotation() {
    return m_rotation; 
  }

  Vector3 Plug::getFaceToFaceRotation(Plug *plug) { 
    Vector3 o1 = getPosition();
    Vector3 o2 = plug->getPosition();
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

