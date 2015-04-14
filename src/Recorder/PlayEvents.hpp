//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_RECORDER_PLAYEVENTS_H
#define SYNTHETICS_RECORDER_PLAYEVENTS_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Event.hpp"
#include "Configurator.hpp"

namespace Synthetics {
  namespace Recorder {
    class PlayEvents : public Polycode::EventHandler {
      public:
        PlayEvents(Polycode::Core *core, Configurator *conf);
        ~PlayEvents();
        Number emitEvent();

      private:
        bool m_on;
        Polycode::Core *m_core;
        Configurator *m_conf;
        FILE *m_file;
    };
  }
}
#endif
