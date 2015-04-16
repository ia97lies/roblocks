//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_MENU_H
#define SYNTHETICS_CONSTRUCTOR_MENU_H

#include <vector>
#include "MenuEntry.hpp"

namespace Synthetics {
  namespace Constructor {
    class Menu {
      public:
        Menu();
        ~Menu();

        void addEntry(MenuEntry *entry);
        MenuEntry *getEntry(int index);
        int getNoEntries();

      private:
        std::vector<MenuEntry *> m_entries;
    };
  }
}
#endif
