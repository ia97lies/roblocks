//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_MENUENTRY_H
#define SYNTHETICS_CONSTRUCTOR_MENUENTRY_H

#include "PolyEntity.h"
#include "Command.hpp"

namespace Synthetics {
  namespace Constructor {
    class MenuEntry {
      public:
        MenuEntry(Command *command, Polycode::Entity *label);
        ~MenuEntry();

        Command *getCommand();
        Polycode::Entity *getLabel();
        Polycode::Entity *getHook();

      private:
        Command *m_command;
        Polycode::Entity *m_label;
        Polycode::Entity *m_hook;
    };
  }
}
#endif
