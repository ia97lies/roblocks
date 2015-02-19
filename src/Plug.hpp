//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_PLUG_H
#define SYNTHETICS_PLUG_H

#include "PolyEntity.h"
#include "PolyVector3.h"
#include "Compound.hpp"

namespace Synthetics {
  class Plug {
    public:
      Plug(Polycode::Vector3 position, Polycode::Vector3 rotation);
      virtual ~Plug();

      virtual Polycode::Vector3 getPosition();
      virtual Polycode::Vector3 getRotation();
      virtual Polycode::Vector3 getFaceToFaceRotation(Plug *plug); 
      virtual Polycode::Entity *getShape();
      virtual void setValue(Polycode::Vector3 value);
      virtual Polycode::Vector3 getValue();
      virtual void setInput(bool on);
      virtual void setInOut(bool on);
      virtual void setDeaf(bool on);
      virtual bool isInput();
      virtual bool isOutput();
      virtual void activate(bool on);
      virtual bool isActivate(); 
      virtual void setConnectedPlug(Plug *plug);
      virtual void unsetConnectedPlug();
      virtual Plug *getConnectedPlug();
      virtual void setParent(Compound *compound); 
      virtual Compound *getParent(); 

    private:
      Polycode::Vector3 m_position;
      Polycode::Vector3 m_rotation;
      Polycode::Entity *m_shape;
      Polycode::Vector3 m_value;
      bool m_input;
      bool m_output;
      bool m_on;
      Plug *m_connectedPlug;
      Compound *m_parent;

      void setColor();
  };
}

#endif
