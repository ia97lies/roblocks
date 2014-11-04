#ifndef _SYN_OBJECT_H_
#define _SYN_OBJECT_H_

class SynObject {
  public:
    SynObject() {};
    ~SynObject() {};

    virutal void add(const SynObject &object) = 0;
}

#endif
