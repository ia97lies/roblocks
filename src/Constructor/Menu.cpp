//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Menu.hpp"

namespace Synthetics {
  namespace Constructor {
    Menu::Menu() {
      m_shape = new Polycode::Entity();
    }

    Menu::~Menu() {}

    void Menu::addEntry(MenuEntry *entry) {
      m_shape->addChild(entry->getLabel());
      m_entries.push_back(entry);
    }

    MenuEntry *Menu::getEntry(int index) {
      return m_entries.at(index);
    }

    MenuEntry *Menu::getEntry(Polycode::Entity *label) {
      for (int i = 0; i < getNoEntries(); i++) {
        if (m_entries.at(i)->getLabel() == label) {
          return m_entries.at(i);
        }
      }
      return NULL;
    }

    int Menu::getNoEntries() { 
      return m_entries.size();
    }

    Polycode::Entity *Menu::getShape() {
      return m_shape;
    }
  }
}

