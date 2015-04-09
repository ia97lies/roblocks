//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_SHOWKEYHITS_DISPLAY_H
#define SYNTHETICS_SHOWKEYHITS_DISPLAY_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "KeyLabel.hpp"
#include "Configurator.hpp"

namespace Synthetics {
  namespace ShowKeyHits {
    class Display : public Polycode::EventHandler {
      public:
        Display(Polycode::Core *core, Configurator *conf);
        ~Display();
        void handleEvent(Polycode::Event *e);
        void update(Number dt);
        void activate(bool on); 

      private:
        Polycode::Core *m_core;
        Polycode::Scene *m_scene;
        Configurator *m_conf;
        int m_i;
        KeyLabel *m_label[2];

    };
  }
}
#endif
