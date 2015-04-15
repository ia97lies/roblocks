//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_COMMAND_NONE_H
#define SYNTHETICS_CONSTRUCTOR_COMMAND_NONE_H

#include "Command.hpp"

namespace Synthetics {
  namespace Constructor {

    class CommandNone : public Command {
      public:
        virtual ~CommandNone() {}
        virtual bool execute() { return true; }
        virtual void undo() {}
    };
  }
}

#endif
