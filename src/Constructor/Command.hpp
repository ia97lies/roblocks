//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_COMMAND_H
#define SYNTHETICS_CONSTRUCTOR_COMMAND_H

using namespace Polycode;

namespace Synthetics {
  namespace Constructor {

    class Command {
      virtual ~Command() {}
      virtual void execute() = 0;
      virtual void undo() = 0;
    }
  }
}

#endif
