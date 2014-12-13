//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
#include "UnitPosition.hpp"

using namespace Polycode;

namespace Synthetics {
  UnitPosition::UnitPosition(Vector3 shift, Vector3 orientation) {
    m_shift = shift;
  }

  UnitPosition::~UnitPosition() {}

  Polycode::Vector3 UnitPosition::getShift() { 
    return m_shift; 
  }
}

