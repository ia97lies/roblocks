//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_HISTORY_H
#define SYNTHETICS_CONSTRUCTOR_HISTORY_H

#include <vector>
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
        int m_size;
        int m_cur;
        std::vector<Command *>m_commands;
    };
  }
}

#endif
