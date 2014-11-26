//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_UNIT_EVENT_H
#define SYNTHETICS_UNIT_EVENT_H

#include <Polycode.h>
#include "PolycodeView.h"

namespace Synthetics {

  class UnitEvent : public ::Polycode::Event {
    public:
      UnitEvent(int eventCode, ::Polycode::Vector3 value);
      virtual ~UnitEvent();
      void setValue(::Polycode::Vector3 value);
      ::Polycode::Vector3 getValue();

    private:
      ::Polycode::Vector3 m_value;
  };

}

#endif
