//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_DEVICE_H
#define SYNTHETICS_DEVICE_H

#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"

namespace Synthetics {

  class Event {
    public:
      Event() {
        m_val = Polycode::Vector3(0, 0, 0);
      }
      virtual ~Event() {};
      void setValue(Polycode::Vector3 val) {
        m_val = val;
      }
      Polycode::Vector3 getValue() {
        return m_val;
      }
    private:
      Polycode::Vector3 m_val;
  }

  class Shape {
    public:
      virtual ~Shape() {};

      virtual addFace(Polycode::Vector3 pos, void *plug) = 0;
      virtual int getFace(void *plug) = 0;
  }

  class Device {
    public:
      virtual ~Device() {};

      virtual int getNoShapes() = 0;
      virtual Shape *getShape(void *plug) = 0;
      virtual Shape *getShape(int i) = 0;
      virtual void handleEvent(Event *event) = 0;
  };

  typedef Block *(*BlockCreateFn)(Polycode::CollisionScene *scene);
}

#endif
