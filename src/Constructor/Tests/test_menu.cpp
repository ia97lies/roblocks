//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestMenu
#include <boost/test/unit_test.hpp>
#include "Constructor/Menu.hpp"
#include "Constructor/MenuEntry.hpp"
#include "PolyCoreMock.hpp"

using namespace Synthetics::Constructor;

//----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_menu_instantiate) {
  Menu menu;
}

BOOST_AUTO_TEST_CASE(test_menu_empty) {
  Menu menu;
  BOOST_CHECK_EQUAL(0, menu.getNoEntries());
}

//----------------------------------------------------------------------------
class MenuOneEntryFixture {
  public:
    MenuOneEntryFixture() {
      new PolyCoreMock();
      menu.addEntry(new MenuEntry());
    }

    Menu menu;
};

BOOST_FIXTURE_TEST_SUITE(MenuOneEntry, MenuOneEntryFixture)

  BOOST_AUTO_TEST_CASE(test_menu_check_entry) {
    BOOST_CHECK_EQUAL(1, menu.getNoEntries());
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_entry) {
    BOOST_CHECK(menu.getEntry(0));
  }

  BOOST_AUTO_TEST_CASE(test_menu_add_another_entry) {
    menu.addEntry(new MenuEntry());
    BOOST_CHECK_EQUAL(2, menu.getNoEntries());
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_another_entry) {
    menu.addEntry(new MenuEntry());
    BOOST_CHECK(menu.getEntry(1));
  }

BOOST_AUTO_TEST_SUITE_END()
