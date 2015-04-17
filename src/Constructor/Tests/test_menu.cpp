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

//----------------------------------------------------------------------------
class MenuEmptyFixture {
  public:
    MenuEmptyFixture() {
      new PolyCoreMock();
    }

    Menu menu;
};

BOOST_FIXTURE_TEST_SUITE(MenuEmpty, MenuEmptyFixture)

  BOOST_AUTO_TEST_CASE(test_menu_empty) {
    BOOST_CHECK_EQUAL(0, menu.getNoEntries());
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_entry_by_index) {
    BOOST_CHECK_THROW(menu.getEntry(0), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_entry_by_shape) {
    MenuEntry *entry = new MenuEntry();
    BOOST_CHECK(menu.getEntry(entry->getLabel()) == NULL);
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_entry_by_null_shape) {
    BOOST_CHECK(menu.getEntry((Polycode::Entity *)NULL) == NULL);
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_shape) {
    BOOST_CHECK(dynamic_cast<Polycode::Entity *>(menu.getShape()));
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_num_entity_childs_in_shape) {
    BOOST_CHECK(menu.getShape()->getNumChildren() == 0);
  }

BOOST_AUTO_TEST_SUITE_END()

//----------------------------------------------------------------------------
class MenuOneEntryFixture {
  public:
    MenuOneEntryFixture() {
      new PolyCoreMock();
      entry = new MenuEntry();
      menu.addEntry(entry);
    }

    MenuEntry *entry;
    Menu menu;
};

BOOST_FIXTURE_TEST_SUITE(MenuOneEntry, MenuOneEntryFixture)

  BOOST_AUTO_TEST_CASE(test_menu_check_entry) {
    BOOST_CHECK_EQUAL(1, menu.getNoEntries());
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_entry_by_index) {
    BOOST_CHECK(menu.getEntry(0) == entry);
  }

  BOOST_AUTO_TEST_CASE(test_menu_add_another_entry) {
    menu.addEntry(new MenuEntry());
    BOOST_CHECK_EQUAL(2, menu.getNoEntries());
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_entry_by_shape) {
    BOOST_CHECK(menu.getEntry(entry->getLabel()) == entry);
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_entry_by_null_shape) {
    BOOST_CHECK(menu.getEntry((Polycode::Entity *)NULL) == NULL);
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_num_children_in_shape) {
    BOOST_CHECK(menu.getShape()->getNumChildren() == 1);
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_label_entity_in_shape) {
    Polycode::Entity *label = entry->getLabel();
    BOOST_CHECK(menu.getShape()->getChildAtIndex(0) == label);
  }

BOOST_AUTO_TEST_SUITE_END()

//----------------------------------------------------------------------------
class MenuManyEntryFixture {
  public:
    MenuManyEntryFixture() {
      new PolyCoreMock();
      entry[0] = new MenuEntry();
      entry[1] = new MenuEntry();
      entry[2] = new MenuEntry();
      menu.addEntry(entry[0]);
      menu.addEntry(entry[1]);
      menu.addEntry(entry[2]);
    }

    Menu menu;
    MenuEntry *entry[3];
};

BOOST_FIXTURE_TEST_SUITE(MenuManyEntry, MenuManyEntryFixture)

  BOOST_AUTO_TEST_CASE(test_menu_add_another_entry) {
    BOOST_CHECK_EQUAL(3, menu.getNoEntries());
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_another_entry) {
    BOOST_CHECK(menu.getEntry(1));
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_first_entry) {
    BOOST_CHECK(menu.getEntry(0));
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_last_entry) {
    BOOST_CHECK(menu.getEntry(2));
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_first_entry_by_shape) {
    BOOST_CHECK(menu.getEntry(entry[0]->getLabel()) == entry[0]);
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_last_entry_by_shape) {
    BOOST_CHECK(menu.getEntry(entry[2]->getLabel()) == entry[2]);
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_entry_by_shape) {
    BOOST_CHECK(menu.getEntry(entry[1]->getLabel()) == entry[1]);
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_entry_by_null_shape) {
    BOOST_CHECK(menu.getEntry((Polycode::Entity *)NULL) == NULL);
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_num_children_in_shape) {
    BOOST_CHECK(menu.getShape()->getNumChildren() == 3);
  }

  BOOST_AUTO_TEST_CASE(test_menu_get_label_entity_in_shape) {
    Polycode::Entity *label = entry[1]->getLabel();
    BOOST_CHECK(menu.getShape()->getChildAtIndex(1) == label);
  }

BOOST_AUTO_TEST_SUITE_END()

