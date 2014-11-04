#ifndef _SYNTHETICS_PHYSIC_H_
#define _SYNTHETICS_PHYSIC_H_

#include "Object.hpp"

namespace Synthetics {
  class Physic : Object {
    public:
      Physic() {};
      ~Physic() {};

      virtual void getTransform(float *transform);
  }
}
#endif
