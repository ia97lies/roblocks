#ifndef _SYNTHETICS_HUB_H_
#define _SYNTHETICS_HUB_H_

#include "Object.hpp"

namespace Synthetics {
  class Hub : Object {
    public:
      Hub() {};
      ~Hub() {};

      virtual void connect(const SynObject &block);
      virtual void setSide(int site);
      virtual int getSide();
  }
}
#endif
