//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_TEST_UNIT_MOCK_H
#define SYNTHETICS_TEST_UNIT_MOCK_H

#include <Polycode.h>
#include "PolycodeView.h"

#include "Unit.hpp"

namespace Synthetics {
  namespace Tests {

    class UnitMock : public Unit {
      public:
        UnitMock() {};
        virtual ~UnitMock() {};

        virtual void init() {};
        virtual UnitPlugging *getPlugging() { return NULL; };
        virtual void setActive(bool on) {}; 
        virtual Polycode::ScenePrimitive * getPolycodeObject() { return NULL; };
        virtual void handleEvent(Polycode::Event *event) {};
    };
  }
}

#endif
