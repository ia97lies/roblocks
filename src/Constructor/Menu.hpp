//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_MENU_H
#define SYNTHETICS_CONSTRUCTOR_MENU_H

#include <vector>
#include "PolyEntity.h"
#include "MenuEntry.hpp"

namespace Synthetics {
  namespace Constructor {
    class Menu {
      public:
        Menu();
        ~Menu();

        void addEntry(MenuEntry *entry);
        MenuEntry *getEntry(int index);
        MenuEntry *getEntry(Polycode::Entity *label);
        int getNoEntries();
        Polycode::Entity *getShape();

      private:
        std::vector<MenuEntry *> m_entries;
        Polycode::Entity *m_shape;
    };
  }
}
#endif
