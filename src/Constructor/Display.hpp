//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_DISPLAY_H
#define SYNTHETICS_CONSTRUCTOR_DISPLAY_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"
#include "PolyUIFileDialog.h"

#include "FileManager.hpp"
#include "MovingCamera.hpp"
#include "Robot.hpp"
#include "Configurator.hpp"
#include "SelectorDisplay.hpp"
#include "Components/Factory.hpp"

namespace Synthetics {
  namespace Constructor {
    class Display : public Polycode::EventHandler {
      public:
        Display(Polycode::Core *core, Configurator *conf, Components::Factory *factory);
        ~Display();
        void handleEvent(Polycode::Event *e);
        void update();
        void activate(bool on);

      private:
        bool m_on;
        Polycode::Core *m_core;
        Polycode::PhysicsScene *m_scene;
        Polycode::Scene *m_hudScene;
        MovingCamera *m_camera;
        Components::Factory *m_factory;
        Robot *m_robot;
        Configurator *m_conf;
        SelectorDisplay *m_selectorDisplay;
        FileManager *m_fileDialog;
        unsigned int m_lastClickTime;

        void place();
    };
  }
}
#endif
