//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_MODEL_H
#define SYNTHETICS_CONSTRUCTOR_MODEL_H

#include "Polycode.h"
#include "Polycode3DPhysics.h"
#include "Component.hpp"
#include "Part.hpp"
#include "Plug.hpp"

namespace Synthetics {
  namespace Constructor {
    class Model {
      public:
        Model(); 
        virtual ~Model();

        virtual void setRoot(Component *component);
        virtual Component *getRoot();

      private:
        Component *m_root;
    };
  }
}

#endif
