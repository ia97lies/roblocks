//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_H
#define SYNTHETICS_CONSTRUCTOR_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"

#include "Block.hpp"
#include "MovingCamera.hpp"
#include "BlockFactory.hpp"

namespace Synthetics {
  class Constructor : public Polycode::EventHandler {
    public:
      Constructor(Polycode::Core *core, Polycode::CollisionScene *scene, MovingCamera *camera, BlockFactory *factory);
      ~Constructor();
      void handleEvent(Polycode::Event *e);

    private:
      Polycode::Core *m_core;
      Polycode::CollisionScene *m_scene;
      MovingCamera *m_camera;
      BlockFactory *m_factory;
      Block *m_mother;
      Block *m_curBlock;

      void addMarker();
      void removeMarker();
  };
}
#endif
