//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_DISPLAY_H
#define SYNTHETICS_CONSTRUCTOR_DISPLAY_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"

#include "MovingCamera.hpp"
#include "Controller.hpp"
#include "Robot.hpp"
#include "Configurator.hpp"
#include "SelectorDisplay.hpp"
#include "History.hpp"
#include "Components/Factory.hpp"

namespace Synthetics {
  namespace Constructor {
    class Display : public Controller {
      public:
        Display(Polycode::Core *core, Configurator *conf, Components::Factory *factory);
        ~Display();
        void handleEvent(Polycode::Event *e);
        void update(Number dt);
        void activate();
        void deactivate();

      private:
        bool m_on;
        Polycode::Core *m_core;
        Polycode::PhysicsScene *m_scene;
        MovingCamera *m_camera;
        Components::Factory *m_factory;
        Robot *m_robot;
        Configurator *m_conf;
        SelectorDisplay *m_selectorDisplay;
        History *m_history;

        void place();
    };
  }
}
#endif
