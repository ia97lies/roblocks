#ifndef _SYNTHETICS_GRAPHIC_H_
#define _SYNTHETICS_GRAPHIC_H_

#include "Object.hpp"

namespace Synthetics {
  class Graphic : Object {
    public:
      Graphic() {};
      ~Graphic() {};

      virtual void draw();
  }
}
#endif
