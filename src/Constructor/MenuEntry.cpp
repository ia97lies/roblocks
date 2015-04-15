//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include <string>
#include <cstddef>
#include "CommandNone.hpp"
#include "MenuEntry.hpp"

namespace Synthetics {
  namespace Constructor {
    MenuEntry::MenuEntry() {}
    MenuEntry::~MenuEntry() {}

    Command *MenuEntry::getCommand() { return new CommandNone(); }
    std::string MenuEntry::getLabel() { return "<none>"; }
  }
}

