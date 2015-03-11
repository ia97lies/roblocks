//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_HISTORY_H
#define SYNTHETICS_CONSTRUCTOR_HISTORY_H

#include "Command.hpp"

namespace Synthetics {
  namespace Constructor {
    class History {
      public:
        History(int size);
        ~History();
        void execute(Command *command);
        void undo();
        void redo();

      private:
    };
  }
}

#endif
