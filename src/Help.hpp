//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_HELP_H
#define SYNTHETICS_HELP_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"

#include "Unit.hpp"
#include "UnitFactory.hpp"

namespace Synthetics {
  class Help : public Polycode::EventHandler {
    public:
      Help(Polycode::Core *core);
      ~Help();
      void handleEvent(Polycode::Event *e);

    private:
      Polycode::Core *m_core;
      Polycode::Scene *m_helpScene;
      Polycode::SceneLabel *m_helpText;
  };
}
#endif
