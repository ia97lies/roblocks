//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Menu.hpp"

namespace Synthetics {
  namespace Constructor {
    Menu::Menu() {}

    Menu::~Menu() {}

    void Menu::addEntry(MenuEntry *entry) {
      m_entries.push_back(entry);
    }

    MenuEntry *Menu::getEntry(int index) {
      return m_entries.at(index);
    }

    int Menu::getNoEntries() { 
      return m_entries.size();
    }
  }
}

