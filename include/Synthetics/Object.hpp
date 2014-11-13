//----------------------------------------------------------------------------
// Copyright 2014 Christian Liesch
// Provide under MIT License
//
//----------------------------------------------------------------------------

#ifndef _SYNTHETICS_OBJECT_H_
#define _SYNTHETICS_OBJECT_H_

namespace Synthetics {
  class Object {
    public:
      virtual void connect(Object *object) = 0;
      virtual void reference(Object *object) = 0;
      virtual void draw() = 0;
  };
}

#endif
