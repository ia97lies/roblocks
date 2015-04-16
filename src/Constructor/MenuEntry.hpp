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
        MenuEntry();
        ~MenuEntry();

        void setCommand(Command *);
        Command *getCommand();
        void setLabel(Polycode::Entity *label);
        Polycode::Entity *getLabel();

      private:
        Command *m_command;
        Polycode::Entity *m_label;
    };
  }
}
#endif
