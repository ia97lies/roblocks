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
      new PolyCoreMock();
    }
};

BOOST_FIXTURE_TEST_SUITE(MenuEntryInstantiate, MenuEntryInstantiateFixture)

  BOOST_AUTO_TEST_CASE(test_menu_entry_instantiate) {
    MenuEntry menuEntry;
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_get_default_command) {
    MenuEntry menuEntry;
    BOOST_CHECK(dynamic_cast<CommandNone *>(menuEntry.getCommand()));
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_get_default_label) {
    MenuEntry menuEntry;
    BOOST_CHECK(dynamic_cast<Polycode::SceneLabel *>(menuEntry.getLabel()));
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_get_default_label_position) {
    MenuEntry menuEntry;
    BOOST_CHECK(menuEntry.getLabel()->getPosition() == Vector3(1, 0, 0));
  }

BOOST_AUTO_TEST_SUITE_END()

//----------------------------------------------------------------------------
class MenuEntryCommandFixture {
  public:
    MenuEntryCommandFixture() {
      new PolyCoreMock();
      deleted = false;
      Command *command = new MyCommand(&deleted);
      menuEntry.setCommand(command);
    }
    MenuEntry menuEntry;
    bool deleted;
};

BOOST_FIXTURE_TEST_SUITE(MenuEntryCommand, MenuEntryCommandFixture)

  BOOST_AUTO_TEST_CASE(test_menu_entry_get_my_command) {
    BOOST_CHECK(dynamic_cast<MyCommand *>(menuEntry.getCommand()));
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_set_null_command) {
    menuEntry.setCommand(NULL);
    BOOST_CHECK(dynamic_cast<MyCommand *>(menuEntry.getCommand()));
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_delete_on_overwrite) {
    menuEntry.setCommand(new MyCommand());
    BOOST_CHECK(deleted);
  }
BOOST_AUTO_TEST_SUITE_END()

//----------------------------------------------------------------------------
class MenuEntryLabelFixture {
  public:
    MenuEntryLabelFixture() {
      deleted = false;
      new PolyCoreMock();
      menuEntry.setLabel(new MyEntity(&deleted)); 
    }
    MenuEntry menuEntry;
    bool deleted;
};

BOOST_FIXTURE_TEST_SUITE(MenuEntryLabel, MenuEntryLabelFixture)

  BOOST_AUTO_TEST_CASE(test_menu_entry_get_custom_label) {
    BOOST_CHECK(dynamic_cast<MyEntity *>(menuEntry.getLabel()));
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_overwrite_label) {
    menuEntry.setLabel(new Entity); 
    BOOST_CHECK(dynamic_cast<Entity *>(menuEntry.getLabel()));
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_label_delete_on_overwrite) {
    menuEntry.setLabel(new Entity); 
    BOOST_CHECK(deleted);
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_label_overwrite_null) {
    menuEntry.setLabel(NULL); 
    BOOST_CHECK(dynamic_cast<MyEntity *>(menuEntry.getLabel()));
  }

  BOOST_AUTO_TEST_CASE(test_menu_entry_get_custom_label_pos) {
    BOOST_CHECK(menuEntry.getLabel()->getPosition() == Vector3(1,0,0));
  }

BOOST_AUTO_TEST_SUITE_END()

