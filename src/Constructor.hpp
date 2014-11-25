//----------------------------------------------------------------------------
// The MIT License
// Took the basics from Polycode Examples
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_H
#define SYNTHETICS_CONSTRUCTOR_H

#include <Polycode.h>
#include "PolycodeView.h"

using namespace Polycode;

namespace Synthetics {
  class Constructor : public EventHandler {
    public:
      Constructor(Core *core, Scene *scene);
      ~Constructor();
      void handleEvent(Event *e);

    private:
      Core *m_core;
      Scene *m_scene;
      ScenePrimitive *m_curBox;

      void addChildBox(Vector3 orientation); 
  };
}
#endif
