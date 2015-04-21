//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONTROLER_H
#define SYNTHETICS_CONTROLER_H

#include "PolyEventHandler.h"

namespace Synthetics {
  class Controller : public Polycode::EventHandler {
    public:
      Controller();
      virtual ~Controller();

      virtual void deactivate() = 0;
      virtual void activate() = 0;
      virtual void enter(Controller *controller);
      virtual void leave();

    private:
      Controller *m_parent;
  };
}

#endif
