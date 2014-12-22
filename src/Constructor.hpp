//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_H
#define SYNTHETICS_CONSTRUCTOR_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"

#include "MovingCamera.hpp"
#include "Compounds/Factory.hpp"

namespace Synthetics {
  class Constructor : public Polycode::EventHandler {
    public:
      Constructor(Polycode::Core *core, Polycode::CollisionScene *scene, MovingCamera *camera, Compounds::Factory *factory);
      ~Constructor();
      void handleEvent(Polycode::Event *e);

    private:
      Polycode::Core *m_core;
      Polycode::CollisionScene *m_scene;
      MovingCamera *m_camera;
      Compounds::Factory *m_factory;
  };
}
#endif
