//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestController
#include <boost/test/unit_test.hpp>
#include "Controller.hpp"

using namespace Polycode;
using namespace Synthetics;

class MyController : public Controller {
  public:
    MyController() { on = true; }
    void deactivate() {
      on = false;
    }
    void activate() {
      on = true;
    }

    bool on;
};

// ---------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_instantiate) {
  MyController controller;
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
class EnterControllerFixture {
  public:
    EnterControllerFixture() {
      child.on = false;
      child.enter(&parent);
    }
    MyController parent;
    MyController child;
};

BOOST_FIXTURE_TEST_SUITE(EnterController, EnterControllerFixture)

  BOOST_AUTO_TEST_CASE(test_enter_child_turn_off_parent) {
    BOOST_CHECK_EQUAL(false, parent.on);
  }

  BOOST_AUTO_TEST_CASE(test_enter_child_turn_on_child) {
    BOOST_CHECK_EQUAL(true, child.on);
  }

  BOOST_AUTO_TEST_CASE(test_leave_child_turn_off_child) {
    child.leave();
    BOOST_CHECK_EQUAL(false, child.on);
  }

  BOOST_AUTO_TEST_CASE(test_leave_child_turn_on_parent) {
    child.leave();
    BOOST_CHECK_EQUAL(true, parent.on);
  }

BOOST_AUTO_TEST_SUITE_END()
