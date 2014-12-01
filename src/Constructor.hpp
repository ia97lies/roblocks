//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_H
#define SYNTHETICS_CONSTRUCTOR_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Unit.hpp"
#include "UnitFactory.hpp"

namespace Synthetics {
  class Constructor : public Polycode::EventHandler {
    public:
      Constructor(Polycode::Core *core, Polycode::Scene *scene, UnitFactory *factory);
      ~Constructor();
      void handleEvent(Polycode::Event *e);

    private:
      int m_curFace;
      Polycode::Core *m_core;
      Polycode::Scene *m_scene;
      UnitFactory *m_factory;
      Polycode::ScenePrimitive *m_marker;
      Unit *m_selectedUnit;
  };
}
#endif
