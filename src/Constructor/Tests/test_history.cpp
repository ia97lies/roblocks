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

BOOST_AUTO_TEST_CASE(test_history_size_3_add_6_executes_4_undo_4_redo) {
  int didExecute = 0;
  int didUndo = 0;
  bool deleted[6] = { false, false, false, false, false, false };
  History *history = new History(3);
  MyCommand *command[6] = { new MyCommand(&didExecute, &didUndo, &deleted[0]),
                            new MyCommand(&didExecute, &didUndo, &deleted[1]),
                            new MyCommand(&didExecute, &didUndo, &deleted[2]),
                            new MyCommand(&didExecute, &didUndo, &deleted[3]),
                            new MyCommand(&didExecute, &didUndo, &deleted[4]),
                            new MyCommand(&didExecute, &didUndo, &deleted[5]) };
  history->execute(command[0]);
  history->execute(command[1]);
  history->execute(command[2]);
  BOOST_CHECK(!deleted[0]);
  BOOST_CHECK(!deleted[1]);
  BOOST_CHECK(!deleted[2]);
  history->execute(command[3]);
  BOOST_CHECK(deleted[0]);
  BOOST_CHECK(!deleted[1]);
  BOOST_CHECK(!deleted[2]);
  BOOST_CHECK(!deleted[3]);
  history->execute(command[4]);
  history->execute(command[5]);
  BOOST_CHECK(deleted[0]);
  BOOST_CHECK(deleted[1]);
  BOOST_CHECK(deleted[2]);
  BOOST_CHECK(!deleted[3]);
  BOOST_CHECK(!deleted[4]);
  BOOST_CHECK(!deleted[5]);
  history->undo();
  history->undo();
  history->undo();
  history->undo();
  // XXX: I AM HERE
  BOOST_CHECK(didUndo == 3);
}

