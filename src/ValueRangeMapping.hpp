//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_VALUE_RANGE_MAPPING_H
#define SYNTHETICS_VALUE_RANGE_MAPPING_H

#include "PolyVector3.h"

namespace Synthetics {
  class ValueRangeMapping {
    public:
      ValueRangeMapping(Polycode::Vector3 min, Polycode::Vector3 max, Polycode::Vector3 value);
      virtual ~ValueRangeMapping();

      Polycode::Vector3 value();
      Polycode::Vector3 map();

    private:
      Polycode::Vector3 m_min;
      Polycode::Vector3 m_max;
      Polycode::Vector3 m_value;
  };
}

#endif
