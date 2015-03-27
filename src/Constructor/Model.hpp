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
        virtual void activate(Polycode::Entity *shape);
        virtual Component *getActiveComponent();
        virtual Part *getActivePart();
        virtual Plug *getActivePlug();

      private:
        Component *m_root;
        Component *m_activeComponent;
        Part *m_activePart;
        Plug *m_activePlug;
    };
  }
}

#endif
