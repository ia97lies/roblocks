#define BOOST_TEST_MODULE UnitPlugging
#include <boost/test/unit_test.hpp>

#include "Unit/Component.hpp"

using namespace Polycode;
using namespace Synthetics;

BOOST_AUTO_TEST_CASE(test_creat_destroy_component) {
  Unit::Component parent(0);
}

BOOST_AUTO_TEST_CASE(test_add_one_plug) {
  Unit::Component parent(1);
  void *plug = malloc(1);
  Unit::Orientation orientation(Vector3(1, 2, 3));
  parent.addPlug(0, orientation, plug);
  BOOST_CHECK(parent.getOrientation(0).get() == Vector3(1, 2, 3));
  //BOOST_CHECK(parent.getFace(plug) == 0);
}

