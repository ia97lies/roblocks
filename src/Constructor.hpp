//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_H
#define SYNTHETICS_CONSTRUCTOR_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"

#include "PolycodeUnit.hpp"
#include "MovingCamera.hpp"
#include "UnitFactory.hpp"

namespace Synthetics {
  class Constructor : public Polycode::EventHandler {
    public:
      Constructor(Polycode::Core *core, Polycode::CollisionScene *scene, MovingCamera *camera, UnitFactory *factory);
      ~Constructor();
      void handleEvent(Polycode::Event *e);

    private:
      Polycode::Core *m_core;
      Polycode::CollisionScene *m_scene;
      MovingCamera *m_camera;
      UnitFactory *m_factory;
      PolycodeUnit *m_mother;
      PolycodeUnit *m_curUnit;

      void addMarker();
      void removeMarker();
  };
}
#endif
