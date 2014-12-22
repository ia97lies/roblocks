//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_HELP_H
#define SYNTHETICS_HELP_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"

#include "Compounds/Factory.hpp"
#include "Configurator.hpp"

namespace Synthetics {
  class HeadUpDisplay : public Polycode::EventHandler {
    public:
      HeadUpDisplay(Polycode::Core *core, Configurator *conf, Compounds::Factory *factory);
      ~HeadUpDisplay();
      void handleEvent(Polycode::Event *e);

    private:
      Configurator *m_conf;
      Polycode::Core *m_core;
      Polycode::Scene *m_hudScene;
      Polycode::SceneLabel *m_hudHelp;
      bool m_on;
  };
}
#endif
