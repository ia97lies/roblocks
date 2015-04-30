//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include <stdexcept>
#include "Hinge.hpp"

namespace Synthetics {
  Hinge::Hinge(HingePoint *point1, HingePoint *point2) {
    m_point[0] = point1;
    m_point[1] = point2;
  }

  Hinge::~Hinge() {}

  HingePoint *Hinge::getPoint(size_t index) { 
    if (index > 1) {
      throw std::out_of_range("Only to hinge points exist");
    }
    return m_point[index]; 
  }

}

