//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_H
#define SYNTHETICS_CONSTRUCTOR_H

#include <Polycode.h>
#include "PolycodeView.h"

namespace Synthetics {
  class Constructor : public Polycode::EventHandler {
    public:
      Constructor(Polycode::Core *core, Polycode::Scene *scene);
      ~Constructor();
      void handleEvent(Polycode::Event *e);

    private:
      Polycode::Core *m_core;
      Polycode::Scene *m_scene;
      Polycode::ScenePrimitive *m_curBox;

      void addChildBox(Polycode::Vector3 orientation); 
  };
}
#endif
