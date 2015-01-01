//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_SELECTOR_DISPLAY_H
#define SYNTHETICS_SELECTOR_DISPLAY_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"

#include "Components/Factory.hpp"
#include "Configurator.hpp"

namespace Synthetics {
  class SelectorDisplay : public Polycode::EventHandler {
    public:
      SelectorDisplay(Polycode::Core *core, Configurator *conf, Components::Factory *factory);
      ~SelectorDisplay();
      void handleEvent(Polycode::Event *e);
      void turnOn(bool on); 
      std::string getText();

    private:
      Configurator *m_conf;
      Polycode::Core *m_core;
      Polycode::CollisionScene *m_scene;
      PolycodeFacade *m_polycodeFacade;
      Polycode::Scene *m_hudScene;
      Polycode::SceneLabel *m_label;
      Components::Factory *m_factory;
      int m_index;
      std::string m_text; 
      std::vector<Component *> m_components;
  };
}
#endif
