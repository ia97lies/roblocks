//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "HingePoint.hpp"

using namespace Polycode; 

namespace Synthetics {
  HingePoint::HingePoint(Part *part, Vector3 pivot, Vector3 axis) {
    m_part = part;
    m_pivot = pivot;
    m_axis = axis;
  }

  HingePoint::~HingePoint() { }

  Part *HingePoint::getPart() { return m_part; }
  Polycode::Vector3 HingePoint::getPivot() { return m_pivot; }
  Polycode::Vector3 HingePoint::getAxis() { return m_axis; }
}

