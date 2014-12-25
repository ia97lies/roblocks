//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_PLUG_H
#define SYNTHETICS_PLUG_H

#include "PolyVector3.h"

namespace Synthetics {
  class Plug {
    public:
      Plug(Polycode::Vector3 position, Polycode::Vector3 rotation);
      ~Plug();

      void setUserData(void *data);
      void *getUserData();
      Polycode::Vector3 getPosition();
      Polycode::Vector3 getRotation();
      Polycode::Vector3 getFaceToFaceRotation(Plug *plug); 

    private:
      Polycode::Vector3 m_position;
      Polycode::Vector3 m_rotation;
      void *m_data;
  };
}

#endif
