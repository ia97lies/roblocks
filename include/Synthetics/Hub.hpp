//----------------------------------------------------------------------------
// Copyright 2014 Christian Liesch
// Provide under MIT License
//
//----------------------------------------------------------------------------

#ifndef _SYNTHETICS_HUB_H_
#define _SYNTHETICS_HUB_H_

#include "Synthetics/Object.hpp"

namespace Synthetics {
  class Hub : Object {
    public:
      Hub();
      ~Hub();

      virtual void connect(Object *object);
      virtual void reference(Object *object);
      virtual void setSide(int side);
      virtual int getSide();
      virtual void draw();

    private:
      Object *connections[6];
      Object *references[6];
      int currentSideIndex;
      int maxSide;
  };
}
#endif
