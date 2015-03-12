//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_COMMAND_H
#define SYNTHETICS_CONSTRUCTOR_COMMAND_H

namespace Synthetics {
  namespace Constructor {

    class Command {
      public:
        virtual ~Command() {}
        virtual void execute() = 0;
        virtual void undo() = 0;
    };
  }
}

#endif
