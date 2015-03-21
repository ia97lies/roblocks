//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestConstructorHistory
#include <boost/test/unit_test.hpp>
#include "PolycodeFacade.hpp"
#include "Plug.hpp"
#include "Constructor/Command.hpp"
#include "Constructor/History.hpp"

using namespace Synthetics;
using namespace Synthetics::Constructor;
using namespace Polycode;

class MyCommand : public Command {
  public:
    MyCommand(int *didExecute, int *didUndo, bool *deleted) {
      m_didExecute = didExecute;
      m_didUndo = didUndo;
      m_deleted = deleted;
    }
    virtual ~MyCommand() { *m_deleted = true; }
    virtual void execute() { *m_didExecute = *m_didExecute + 1; }
    virtual void undo() { *m_didUndo = *m_didUndo + 1; }
  private:
    int *m_didExecute;
    int *m_didUndo;
    bool *m_deleted;
};

BOOST_AUTO_TEST_CASE(test_history_empty) {
  History *history = new History(1);
  history->undo();
  history->redo();
}


//----------------------------------------------------------------------------
class HistoryOneElementFixture {
  public:
    HistoryOneElementFixture() {
      didExecute = 0;
      didUndo = 0;
      deleted = false;
      history = new History(1);
      command = new MyCommand(&didExecute, &didUndo, &deleted);
    }
    int didExecute;
    int didUndo;
    bool deleted;
    History *history;
    MyCommand *command;
};

BOOST_FIXTURE_TEST_SUITE(HistoryOneElement, HistoryOneElementFixture)

  BOOST_AUTO_TEST_CASE(test_history_execute) {
    history->execute(command);
    BOOST_CHECK(didExecute == 1);
  }

  BOOST_AUTO_TEST_CASE(test_history_execute_not_deleted) {
    history->execute(command);
    BOOST_CHECK(!deleted);
  }

  BOOST_AUTO_TEST_CASE(test_history_undo) {
    history->execute(command);
    history->undo();
    BOOST_CHECK(didUndo == 1);
  }

  BOOST_AUTO_TEST_CASE(test_history_undo_not_deleted) {
    history->execute(command);
    history->undo();
    BOOST_CHECK(!deleted);
  }

  BOOST_AUTO_TEST_CASE(test_history_undo_twice) {
    history->execute(command);
    history->undo();
    history->undo();
    BOOST_CHECK(didUndo == 1);
  }

  BOOST_AUTO_TEST_CASE(test_history_undo_twice_not_deleted) {
    history->execute(command);
    history->undo();
    history->undo();
    BOOST_CHECK(!deleted);
  }

  BOOST_AUTO_TEST_CASE(test_history_2_executes) {
    history->execute(command);
    BOOST_CHECK(didExecute == 1);
    bool deleted2;
    Command *command2 = new MyCommand(&didExecute, &didUndo, &deleted2);
    history->execute(command2);
    BOOST_CHECK(didExecute == 2);
    BOOST_CHECK(deleted);
    BOOST_CHECK(!deleted2);
  }

  BOOST_AUTO_TEST_CASE(test_history_2_executes_first_deleted) {
    history->execute(command);
    BOOST_CHECK(didExecute == 1);
    bool deleted2;
    Command *command2 = new MyCommand(&didExecute, &didUndo, &deleted2);
    history->execute(command2);
    BOOST_CHECK(deleted);
  }

  BOOST_AUTO_TEST_CASE(test_history_2_executes_second_not_deleted) {
    history->execute(command);
    BOOST_CHECK(didExecute == 1);
    bool deleted2;
    Command *command2 = new MyCommand(&didExecute, &didUndo, &deleted2);
    history->execute(command2);
    BOOST_CHECK(!deleted2);
  }

  BOOST_AUTO_TEST_CASE(test_history_undo_redo) {
    history->execute(command);
    history->undo();
    history->redo();
    BOOST_CHECK(didUndo == 1);
    BOOST_CHECK(didExecute == 2);
  }

  BOOST_AUTO_TEST_CASE(test_history_undo_redo_not_deleted) {
    history->execute(command);
    history->undo();
    history->redo();
    BOOST_CHECK(!deleted);
  }

  BOOST_AUTO_TEST_CASE(test_history_undo_redo_twice) {
    history->execute(command);
    history->undo();
    history->redo();
    history->redo();
    BOOST_CHECK(didUndo == 1);
    BOOST_CHECK(didExecute == 2);
  }

  BOOST_AUTO_TEST_CASE(test_history_undo_redo_twice_not_deleted) {
    history->execute(command);
    history->undo();
    history->redo();
    history->redo();
    BOOST_CHECK(!deleted);
  }

BOOST_AUTO_TEST_SUITE_END()


//----------------------------------------------------------------------------
class HistoryMoreElementFixture {
  public:
    HistoryMoreElementFixture() {
      didExecute = 0;
      didUndo = 0;
      history = new History(3);
      for (int i = 0; i < 5; i++) {
        deleted[i] = false;
        command[i] = new MyCommand(&didExecute, &didUndo, &deleted[i]);
      }
    }
    int didExecute;
    int didUndo;
    bool deleted[5];
    History *history;
    MyCommand *command[5];
};

BOOST_FIXTURE_TEST_SUITE(HistoryMoreElement, HistoryMoreElementFixture)

  BOOST_AUTO_TEST_CASE(test_history_fill_up) {
    history->execute(command[0]);
    history->execute(command[1]);
    history->execute(command[2]);
    BOOST_CHECK(!deleted[0]);
    BOOST_CHECK(!deleted[1]);
    BOOST_CHECK(!deleted[2]);
    BOOST_CHECK(didExecute == 3);
  }

  BOOST_AUTO_TEST_CASE(test_history_fill_up_and_one) {
    history->execute(command[0]);
    history->execute(command[1]);
    history->execute(command[2]);
    history->execute(command[3]);
    BOOST_CHECK(deleted[0]);
    BOOST_CHECK(!deleted[1]);
    BOOST_CHECK(!deleted[2]);
    BOOST_CHECK(!deleted[3]);
    BOOST_CHECK(didExecute == 4);
  }

  BOOST_AUTO_TEST_CASE(test_history_clean_up) {
    history->execute(command[0]);
    history->execute(command[1]);
    history->execute(command[2]);
    delete history;
    BOOST_CHECK(deleted[0]);
    BOOST_CHECK(deleted[1]);
    BOOST_CHECK(deleted[2]);
  }

  BOOST_AUTO_TEST_CASE(test_history_undo_beyond_history) {
    history->execute(command[0]);
    history->execute(command[1]);
    history->execute(command[2]);
    history->undo();
    history->undo();
    history->undo();
    history->undo();
    history->undo();
    BOOST_CHECK(didUndo == 3);
  }

  BOOST_AUTO_TEST_CASE(test_history_redo_beyond_history) {
    history->execute(command[0]);
    history->execute(command[1]);
    history->execute(command[2]);
    history->undo();
    history->undo();
    history->undo();
    history->redo();
    history->redo();
    history->redo();
    history->redo();
    history->redo();
    BOOST_CHECK(didExecute == 6);
  }

  BOOST_AUTO_TEST_CASE(test_history_not_full_redo_beyond_history) {
    history->execute(command[0]);
    history->execute(command[1]);
    history->undo();
    history->undo();
    history->redo();
    history->redo();
    history->redo();
    BOOST_CHECK(didExecute == 4);
    // this undo did fail and is also a good hint, that we did not go over boundary
    history->undo();
    BOOST_CHECK(didUndo == 3);
  }

  BOOST_AUTO_TEST_CASE(test_history_undo_execute) {
    history->execute(command[0]);
    history->execute(command[1]);
    history->execute(command[2]);
    history->execute(command[3]);
    history->undo();
    history->undo();
    history->execute(command[4]);
    BOOST_CHECK(deleted[2]);
    BOOST_CHECK(deleted[3]);
  }

  BOOST_AUTO_TEST_CASE(test_history_undo_redo_execute) {
    history->execute(command[0]);
    history->execute(command[1]);
    history->execute(command[2]);
    history->execute(command[3]);
    history->undo();
    history->undo();
    history->undo();
    history->redo();
    history->execute(command[4]);
    BOOST_CHECK(deleted[2]);
    BOOST_CHECK(deleted[3]);
  }

BOOST_AUTO_TEST_SUITE_END()
