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

BOOST_AUTO_TEST_CASE(test_history_execute) {
  int didExecute = 0;
  int didUndo = 0;
  bool deleted = false;
  History *history = new History(1);
  MyCommand *command = new MyCommand(&didExecute, &didUndo, &deleted);
  history->execute(command);
  BOOST_CHECK(didExecute == 1);
  BOOST_CHECK(!deleted);
}

BOOST_AUTO_TEST_CASE(test_history_undo) {
  int didExecute = 0;
  int didUndo = 0;
  bool deleted = false;
  History *history = new History(1);
  MyCommand *command = new MyCommand(&didExecute, &didUndo, &deleted);
  history->execute(command);
  history->undo();
  BOOST_CHECK(didUndo == 1);
  BOOST_CHECK(!deleted);
}

BOOST_AUTO_TEST_CASE(test_history_undo_twice) {
  int didExecute = 0;
  int didUndo = 0;
  bool deleted = false;
  History *history = new History(1);
  MyCommand *command = new MyCommand(&didExecute, &didUndo, &deleted);
  history->execute(command);
  history->undo();
  history->undo();
  BOOST_CHECK(didUndo == 1);
  BOOST_CHECK(!deleted);
}

BOOST_AUTO_TEST_CASE(test_history_size_1_add_2_executes) {
  int didExecute = 0;
  int didUndo = 0;
  bool deleted[2] = { false, false };
  History *history = new History(1);
  MyCommand *command = new MyCommand(&didExecute, &didUndo, &deleted[0]);
  history->execute(command);
  BOOST_CHECK(didExecute == 1);
  command = new MyCommand(&didExecute, &didUndo, &deleted[1]);
  history->execute(command);
  BOOST_CHECK(didExecute == 2);
  BOOST_CHECK(deleted[0]);
  BOOST_CHECK(!deleted[1]);
}

BOOST_AUTO_TEST_CASE(test_history_undo_redo) {
  int didExecute = 0;
  int didUndo = 0;
  bool deleted = false;
  History *history = new History(1);
  MyCommand *command = new MyCommand(&didExecute, &didUndo, &deleted);
  history->execute(command);
  history->undo();
  history->redo();
  BOOST_CHECK(didUndo == 1);
  BOOST_CHECK(didExecute == 2);
  BOOST_CHECK(!deleted);
}

BOOST_AUTO_TEST_CASE(test_history_size_1_undo_redo_twice) {
  int didExecute = 0;
  int didUndo = 0;
  bool deleted = false;
  History *history = new History(1);
  MyCommand *command = new MyCommand(&didExecute, &didUndo, &deleted);
  history->execute(command);
  history->undo();
  history->redo();
  history->redo();
  BOOST_CHECK(didUndo == 1);
  BOOST_CHECK(didExecute == 2);
  BOOST_CHECK(!deleted);
}

BOOST_AUTO_TEST_CASE(test_history_fill_up) {
  int didExecute = 0;
  int didUndo = 0;
  bool deleted[3] = { false, false, false };
  History *history = new History(3);
  MyCommand *command[3] = { new MyCommand(&didExecute, &didUndo, &deleted[0]),
                            new MyCommand(&didExecute, &didUndo, &deleted[1]),
                            new MyCommand(&didExecute, &didUndo, &deleted[2]) };
  history->execute(command[0]);
  history->execute(command[1]);
  history->execute(command[2]);
  BOOST_CHECK(!deleted[0]);
  BOOST_CHECK(!deleted[1]);
  BOOST_CHECK(!deleted[2]);
  BOOST_CHECK(didExecute == 3);
}

BOOST_AUTO_TEST_CASE(test_history_fill_up_and_one) {
  int didExecute = 0;
  int didUndo = 0;
  bool deleted[4] = { false, false, false, false };
  History *history = new History(3);
  MyCommand *command[4] = { new MyCommand(&didExecute, &didUndo, &deleted[0]),
                            new MyCommand(&didExecute, &didUndo, &deleted[1]),
                            new MyCommand(&didExecute, &didUndo, &deleted[2]),
                            new MyCommand(&didExecute, &didUndo, &deleted[3]) };
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
  int didExecute = 0;
  int didUndo = 0;
  bool deleted[3] = { false, false, false };
  History *history = new History(3);
  MyCommand *command[3] = { new MyCommand(&didExecute, &didUndo, &deleted[0]),
                            new MyCommand(&didExecute, &didUndo, &deleted[1]),
                            new MyCommand(&didExecute, &didUndo, &deleted[2]) };
  history->execute(command[0]);
  history->execute(command[1]);
  history->execute(command[2]);
  delete history;
  BOOST_CHECK(deleted[0]);
  BOOST_CHECK(deleted[1]);
  BOOST_CHECK(deleted[2]);
}

BOOST_AUTO_TEST_CASE(test_history_undo_beyond_history) {
  int didExecute = 0;
  int didUndo = 0;
  bool deleted[3] = { false, false, false };
  History *history = new History(3);
  MyCommand *command[3] = { new MyCommand(&didExecute, &didUndo, &deleted[0]),
                            new MyCommand(&didExecute, &didUndo, &deleted[1]),
                            new MyCommand(&didExecute, &didUndo, &deleted[2]) };
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
  int didExecute = 0;
  int didUndo = 0;
  bool deleted[3] = { false, false, false };
  History *history = new History(3);
  MyCommand *command[3] = { new MyCommand(&didExecute, &didUndo, &deleted[0]),
                            new MyCommand(&didExecute, &didUndo, &deleted[1]),
                            new MyCommand(&didExecute, &didUndo, &deleted[2]) };
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
  int didExecute = 0;
  int didUndo = 0;
  bool deleted[3] = { false, false, false };
  History *history = new History(3);
  MyCommand *command[3] = { new MyCommand(&didExecute, &didUndo, &deleted[0]),
                            new MyCommand(&didExecute, &didUndo, &deleted[1]),
                            new MyCommand(&didExecute, &didUndo, &deleted[2]) };
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
  int didExecute = 0;
  int didUndo = 0;
  bool deleted[5] = { false, false, false, false, false };
  History *history = new History(4);
  MyCommand *command[5] = { new MyCommand(&didExecute, &didUndo, &deleted[0]),
                            new MyCommand(&didExecute, &didUndo, &deleted[1]),
                            new MyCommand(&didExecute, &didUndo, &deleted[2]),
                            new MyCommand(&didExecute, &didUndo, &deleted[3]),
                            new MyCommand(&didExecute, &didUndo, &deleted[4]) };

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
  int didExecute = 0;
  int didUndo = 0;
  bool deleted[5] = { false, false, false, false, false };
  History *history = new History(4);
  MyCommand *command[5] = { new MyCommand(&didExecute, &didUndo, &deleted[0]),
                            new MyCommand(&didExecute, &didUndo, &deleted[1]),
                            new MyCommand(&didExecute, &didUndo, &deleted[2]),
                            new MyCommand(&didExecute, &didUndo, &deleted[3]),
                            new MyCommand(&didExecute, &didUndo, &deleted[4]) };

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

