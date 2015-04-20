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
    MenuEntry::MenuEntry(Command *command, Entity *label) { 
      m_command = command; 
      m_hook = new Entity();
      m_label = label; 
      m_label->setPosition(1, 0, 0);
      m_hook->addChild(m_label);
    }

    MenuEntry::~MenuEntry() {
      delete m_command;
      m_hook->removeChild(m_label);
      delete m_label;
      delete m_hook;
    }

    Command *MenuEntry::getCommand() { return m_command; }

    Entity *MenuEntry::getLabel() { return m_label; }

    Entity *MenuEntry::getHook() { return m_hook; }
  }
}

