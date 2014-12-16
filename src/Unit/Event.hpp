//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_UNIT_EVENT_H
#define SYNTHETICS_UNIT_EVENT_H

#include "PolyVector3.h"

namespace Synthetics {
  namespace Unit {

    class Event {
      public:
        Event(int eventCode, Polycode::Vector3 value);
        virtual ~Event();
        void setValue(Polycode::Vector3 value);
        Polycode::Vector3 getValue();

      private:
        Polycode::Vector3 m_value;
    };

  }
}

#endif
