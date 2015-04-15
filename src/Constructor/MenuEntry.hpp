//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_MENUENTRY_H
#define SYNTHETICS_CONSTRUCTOR_MENUENTRY_H

#include "Command.hpp"

namespace Synthetics {
  namespace Constructor {
    class MenuEntry {
      public:
        MenuEntry();
        ~MenuEntry();

        Command *getCommand();
        std::string getLabel();
    };
  }
}
#endif
