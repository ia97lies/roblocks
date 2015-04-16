//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include <string>
#include <cstddef>
#include "PolySceneLabel.h"
#include "CommandNone.hpp"
#include "MenuEntry.hpp"

using namespace Polycode;

namespace Synthetics {
  namespace Constructor {
    MenuEntry::MenuEntry() { 
      m_command = new CommandNone(); 
      m_label = new SceneLabel("<none>", 14); 
      m_label->setPosition(1, 0, 0);
    }

    MenuEntry::~MenuEntry() {}

    void MenuEntry::setCommand(Command *command) { 
      if (command != NULL) {
        delete m_command;
        m_command = command; 
      }
    }

    Command *MenuEntry::getCommand() { return m_command; }

    void MenuEntry::setLabel(Entity *label) {
      if (label) {
        delete m_label;
        m_label = label;
        m_label->setPosition(1, 0, 0);
      }
    }

    Entity *MenuEntry::getLabel() { return m_label; }
  }
}

