//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestMenuEntry
#include <boost/test/unit_test.hpp>
#include "Constructor/MenuEntry.hpp"
#include "Constructor/CommandNone.hpp"

using namespace Synthetics::Constructor;

class MyCommand : public Command {
  public:
    MyCommand() {}
    ~MyCommand() {}

    bool execute() { return true; }
    void undo() { }
};

//----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_menu_entry_instantiate) {
  MenuEntry menuEntry;
}

BOOST_AUTO_TEST_CASE(test_menu_entry_get_default_command) {
  MenuEntry menuEntry;

  BOOST_CHECK(dynamic_cast<CommandNone *>(menuEntry.getCommand()));
}

BOOST_AUTO_TEST_CASE(test_menu_entry_get_default_label) {
  MenuEntry menuEntry;

  BOOST_CHECK_EQUAL("<none>", menuEntry.getLabel());
}

//----------------------------------------------------------------------------
class MyMenuEntryFixture {
  public:
    MyMenuEntryFixture() {
    }
};

BOOST_FIXTURE_TEST_SUITE(MyMenuEntry, MyMenuEntryFixture)

  BOOST_AUTO_TEST_CASE(test_my_menu_entry_) {
  }

BOOST_AUTO_TEST_SUITE_END()

