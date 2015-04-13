//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_RECORDER_RECORDEVENTS_H
#define SYNTHETICS_RECORDER_RECORDEVENTS_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Configurator.hpp"

namespace Synthetics {
  namespace Recorder {
    class RecordEvents : public Polycode::EventHandler {
      public:
        RecordEvents(Polycode::Core *core, Configurator *conf);
        ~RecordEvents();
        void handleEvent(Polycode::Event *e);
        void update(Number dt);
        void activate(bool on); 

      private:
        bool m_on;
        Polycode::Core *m_core;
        Configurator *m_conf;
        int m_eventCode;
        int m_keyCode;
        wchar_t m_keyCharCode;
        int m_mouseButton;
        Polycode::Vector2 m_mousePosition;

    };
  }
}
#endif
