#ifndef _SYN_OBJECT_H_
#define _SYN_OBJECT_H_

#include "SynObject.hpp"

class SynBlock : SynObject {
  public:
    SynBlock() {};
    ~SynBlock() {};

    enum class Side = {
      left, right, up, down, back, front
    }

    virtual void connect(const SynObject &block);
    virtual void setSide(const Side &side);
    virtual Side getSide();
}

#endif
