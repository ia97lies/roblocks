//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "ValueRangeMapping.hpp"

using namespace Polycode;

namespace Synthetics {
  ValueRangeMapping::ValueRangeMapping(Polycode::Vector3 min, Polycode::Vector3 max, Polycode::Vector3 value) {
    m_min = min;
    m_max = max;

    if (value.x > 100) value.x = 100;
    if (value.y > 100) value.y = 100;
    if (value.z > 100) value.z = 100;
    if (value.x < 0) value.x = 0;
    if (value.y < 0) value.y = 0;
    if (value.z < 0) value.z = 0;
    
    m_value = value;
  }

  ValueRangeMapping::~ValueRangeMapping() {
  }

  Polycode::Vector3 ValueRangeMapping::value() {
    return m_value;
  }

  Polycode::Vector3 ValueRangeMapping::map() {
    Vector3 range = m_max - m_min;
    return m_min + (range * 0.01) * m_value;
  }

}

