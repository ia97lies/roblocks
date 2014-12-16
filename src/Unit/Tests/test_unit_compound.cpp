#define BOOST_TEST_MODULE UnitPlugging
#include <boost/test/unit_test.hpp>

#include "Unit/Compound.hpp"

using namespace Polycode;
using namespace Synthetics;

BOOST_AUTO_TEST_CASE(test_creat_destroy_compound) {
  Unit::Compound parent(0);
}

BOOST_AUTO_TEST_CASE(test_add_one_plug_get_orientation) {
  Unit::Compound parent(1);
  Unit::Orientation orientation(Vector3(1, 2, 3));
  parent.addPlug(0, orientation, NULL);
  BOOST_CHECK(parent.getOrientation(0).get() == Vector3(1, 2, 3));
}

BOOST_AUTO_TEST_CASE(test_add_two_plugs_get_orientation) {
  Unit::Compound parent(2);
  Unit::Orientation orientation1(Vector3(1, 2, 3));
  parent.addPlug(0, orientation1, NULL);
  Unit::Orientation orientation2(Vector3(3, 2, 1));
  parent.addPlug(1, orientation2, NULL);
  BOOST_CHECK(parent.getOrientation(0).get() == Vector3(1, 2, 3));
  BOOST_CHECK(parent.getOrientation(1).get() == Vector3(3, 2, 1));
}

BOOST_AUTO_TEST_CASE(test_add_one_plug_get_face) {
  Unit::Compound parent(1);
  Unit::Orientation orientation(Vector3(0, 0, 0));
  void *plug = malloc(1);
  parent.addPlug(0, orientation, plug);
  BOOST_CHECK(parent.getFace(plug) == 0);
}

BOOST_AUTO_TEST_CASE(test_add_two_plugs_get_face) {
  Unit::Compound parent(2);
  Unit::Orientation orientation(Vector3(0, 0, 0));
  void *plug1 = malloc(1);
  parent.addPlug(0, orientation, plug1);
  void *plug2 = malloc(1);
  parent.addPlug(1, orientation, plug2);
  BOOST_CHECK(parent.getFace(plug1) == 0);
  BOOST_CHECK(parent.getFace(plug2) == 1);
}

