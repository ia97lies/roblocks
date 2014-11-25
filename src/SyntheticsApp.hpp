//----------------------------------------------------------------------------
// The MIT License
// Took the basics from Polycode Examples
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_APP_H
#define SYNTHETICS_APP_H

#include <Polycode.h>
#include "PolycodeView.h"

using namespace Polycode;

namespace Synthetics {
  class SyntheticsApp {
    public:
      SyntheticsApp(PolycodeView *view);
      ~SyntheticsApp();
      void handleEvent(Event *e);
      bool Update();

    private:
      Core *m_core;
      Scene *m_scene;
  };
}
#endif
