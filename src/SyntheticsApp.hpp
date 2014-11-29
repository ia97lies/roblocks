//----------------------------------------------------------------------------
// The MIT License
// Took the basics from Polycode Examples
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_APP_H
#define SYNTHETICS_APP_H

#include <Polycode.h>
#include "PolycodeView.h"

#include "MovingCamera.hpp"
#include "Configurator.hpp"

namespace Synthetics {
  class SyntheticsApp {
    public:
      SyntheticsApp(Polycode::PolycodeView *view);
      ~SyntheticsApp();
      void handleEvent(Polycode::Event *e);
      bool Update();

    private:
      Polycode::Core *m_core;
      Polycode::Scene *m_scene;
      MovingCamera *m_camera;
      Configurator *m_conf;
  };
}
#endif
