//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_UNIT_H
#define SYNTHETICS_UNIT_H

#include <Polycode.h>
#include "PolycodeView.h"

#include "UnitEvent.hpp"

using namespace Polycode;

namespace Synthetics {
  UnitEvent::UnitEvent(int eventCode, Vector3 value) : Event(eventCode) {
    m_value = value;
  }

  UnitEvent::~UnitEvent() {
  }

  void UnitEvent::setValue(Vector3 value) {
    m_value = value;
  }
  
  Vector3 UnitEvent::getValue() {
    return m_value;
  }
}

#endif
