//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Menu.hpp"

using namespace Polycode;

namespace Synthetics {
  namespace Constructor {
    Menu::Menu() {
      m_shape = new Polycode::Entity();
    }

    Menu::~Menu() {}

    void Menu::addEntry(MenuEntry *entry) {
      int size = getNoEntries();
      m_shape->addChild(entry->getLabel());
      m_entries.push_back(entry);
      entry->getHook()->setRotationEuler(Vector3(0.0, 0.0, size * 45.0));
      entry->getLabel()->setRotationEuler(Vector3(0.0, 0.0, -size * 45.0));
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

