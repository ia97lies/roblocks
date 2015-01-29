//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_EXCEPTIONS_H
#define SYNTHETICS_EXCEPTIONS_H

#include <exception>

namespace Synthetics {
  class AlreadyExistException : public std::exception {
    public:
      const char * what () const throw () {
        return "Entry already exist";
      }
  };
}

#endif
