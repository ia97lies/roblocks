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

      virtual Polycode::Vector3 getPosition();
      virtual Polycode::Vector3 getRotation();
      virtual float getWidth();
      virtual Polycode::Vector3 getFaceToFaceRotation(Plug *plug); 
      virtual Polycode::Entity *getShape();
      virtual void activate(bool on);
      virtual bool isActivate(); 

    private:
      Polycode::Vector3 m_position;
      Polycode::Vector3 m_rotation;
      Polycode::Entity *m_shape;
      bool m_on;
  };
}

#endif
