//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestMenuEntry
#include <boost/test/unit_test.hpp>
#include "PolyEntity.h"
#include "PolySceneLabel.h"
#include "PolyCoreMock.hpp"
#include "Constructor/MenuEntry.hpp"
#include "Constructor/CommandNone.hpp"

using namespace Polycode;
using namespace Synthetics::Constructor;

class MyEntity : public Polycode::Entity {
  public:
    MyEntity(bool *_deleted = NULL) {
      deleted = _deleted;
    }
    ~MyEntity() {
      if (deleted) {
        *deleted = true;
      }
    }
    bool *deleted;
};

class MyCommand : public Command {
  public:
    MyCommand(bool *_deleted = NULL) {
      deleted = _deleted;
    }
    ~MyCommand() {
      if (deleted) {
        *deleted = true;
      }
    }

    bool execute() { return true; }
    void undo() { }
    bool *deleted;
};

//----------------------------------------------------------------------------
class MenuEntryInstantiateFixture {
  public:
    MenuEntryInstantiateFixture() {
      commandDeleted = false;
      labelDeleted = false;
      new PolyCoreMock();
      command = new MyCommand(&commandDeleted);
      label = new MyEntity(&labelDeleted);
      menuEntry = new MenuEntry(command, label);
    }
    MenuEntry *menuEntry;
    Command *command;
    Entity *label;
    bool commandDeleted;
    bool labelDeleted;
};

BOOST_FIXTURE_TEST_SUITE(MenuEntryInstantiate, MenuEntryInstantiateFixture)

  BOOST_AUTO_TEST_CASE(test_menu_entry_getCommand) {
    BOOST_CHECK(menuEntry->getCommand() == command);
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_getLabel) {
    BOOST_CHECK(menuEntry->getLabel() == label);
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_getHook) {
    BOOST_CHECK(menuEntry->getHook() == label->getParentEntity());
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_get_label_pos) {
    BOOST_CHECK(menuEntry->getLabel()->getPosition() == Vector3(1,0,0));
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_destroy_check_command_deleted) {
    delete menuEntry;
    BOOST_CHECK(commandDeleted);
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_destroy_check_label_deleted) {
    delete menuEntry;
    BOOST_CHECK(labelDeleted);
  }

BOOST_AUTO_TEST_SUITE_END()


