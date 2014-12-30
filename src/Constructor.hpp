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
#include "Components/Factory.hpp"

namespace Synthetics {
  class Constructor : public Polycode::EventHandler {
    public:
      Constructor(Polycode::Core *core, Polycode::CollisionScene *scene, MovingCamera *camera, Components::Factory *factory);
      ~Constructor();
      void handleEvent(Polycode::Event *e);

    private:
      Polycode::Core *m_core;
      Polycode::CollisionScene *m_scene;
      MovingCamera *m_camera;
      std::string m_selectedComponent; 
      Components::Factory *m_factory;
      Robot *m_mother;
  };
}
#endif
