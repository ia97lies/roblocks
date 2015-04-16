//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include <string>
#include <cstddef>
#include "CommandNone.hpp"
#include "MenuEntry.hpp"

namespace Synthetics {
  namespace Constructor {
    MenuEntry::MenuEntry() { m_command = new CommandNone(); }
    MenuEntry::~MenuEntry() {}

    void MenuEntry::setCommand(Command *command) { m_command = command; }
    Command *MenuEntry::getCommand() { return m_command; }
    std::string MenuEntry::getLabel() { return "<none>"; }
  }
}

