//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_H
#define SYNTHETICS_CONSTRUCTOR_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"

#include "MovingCamera.hpp"
#include "Robot.hpp"
#include "Configurator.hpp"
#include "SelectorDisplay.hpp"
#include "Components/Factory.hpp"

namespace Synthetics {
  class Constructor : public Polycode::EventHandler {
    public:
      Constructor(Polycode::Core *core, Configurator *conf, Components::Factory *factory);
      ~Constructor();
      void handleEvent(Polycode::Event *e);

    private:
      Polycode::Core *m_core;
      Polycode::CollisionScene *m_scene;
      Polycode::Scene *m_hudScene;
      MovingCamera *m_camera;
      Components::Factory *m_factory;
      Robot *m_mother;
      Robot *m_park;
      Configurator *m_conf;
      SelectorDisplay *m_selectorDisplay;
  };
}
#endif
