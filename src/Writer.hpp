//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_WRITER_H
#define SYNTHETICS_WRITER_H

namespace Synthetics {
  class Writer {
    public:
      virtual ~Writer() {};
      virtual void write(std::string string) = 0;
  };
}

#endif
