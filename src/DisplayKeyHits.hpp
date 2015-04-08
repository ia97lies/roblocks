//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_DISPLAYKEYHITS_H
#define SYNTHETICS_DISPLAYKEYHITS_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Configurator.hpp"

namespace Synthetics {
  class DisplayKeyHits : public Polycode::EventHandler {
    public:
      DisplayKeyHits(Polycode::Core *core, Configurator *conf);
      ~DisplayKeyHits();
      void handleEvent(Polycode::Event *e);
      void update(Number dt);
      void activate(bool on); 

    private:
      Polycode::Core *m_core;
      Polycode::Scene *m_scene;
      Configurator *m_conf;
      int m_i;
      Polycode::SceneLabel *m_label[2];

  };
}
#endif
