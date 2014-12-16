//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include <Polycode.h>
#include "PolycodeView.h"

#include "Event.hpp"

using namespace Polycode;

namespace Synthetics {
  namespace Unit {
    Event::Event(int eventCode, Vector3 value) {
      m_value = value;
    }

    Event::~Event() {
    }

    void Event::setValue(Vector3 value) {
      m_value = value;
    }

    Vector3 Event::getValue() {
      return m_value;
    }
  }
}

