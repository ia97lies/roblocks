//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_PLUG_H
#define SYNTHETICS_PLUG_H

#include "PolyEntity.h"
#include "PolyVector3.h"

namespace Synthetics {
  class Plug {
    public:
      Plug(Polycode::Vector3 position, Polycode::Vector3 rotation);
      ~Plug();

      Polycode::Vector3 getPosition();
      Polycode::Vector3 getRotation();
      float getWidth();
      Polycode::Vector3 getFaceToFaceRotation(Plug *plug); 
      Polycode::Entity *getShape();
      void activate(bool on);

    private:
      Polycode::Vector3 m_position;
      Polycode::Vector3 m_rotation;
      Polycode::Entity *m_shape;
      bool m_on;
  };
}

#endif
