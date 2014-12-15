#define BOOST_TEST_MODULE UnitPlugging
#include <stdio.h>
#include <boost/test/unit_test.hpp>

#include "Unit/Orientation.hpp"

using namespace Polycode;
using namespace Synthetics;

BOOST_AUTO_TEST_CASE(test_instantiate_orientation) {
  Unit::Orientation orientation(Vector3(1, 2, 3));
}

BOOST_AUTO_TEST_CASE(test_get_orientation) {
  Unit::Orientation orientation(Vector3(1, 2, 3));
  BOOST_CHECK(orientation.get() == Vector3(1, 2, 3));
}

BOOST_AUTO_TEST_CASE(test_get_orientation_versus_orientation_rotation) {
  Unit::Orientation orientation1(Vector3(1, 0, 0));
  Unit::Orientation orientation2(Vector3(-1, 0, 0));
  BOOST_CHECK(orientation1.getRotation(&orientation2) == Vector3(0, 0, 0));
}

BOOST_AUTO_TEST_CASE(test_get_orientation_same_orientation_rotation) {
  Unit::Orientation orientation1(Vector3(1, 0, 0));
  Unit::Orientation orientation2(Vector3(1, 0, 0));
  BOOST_CHECK(orientation1.getRotation(&orientation2) == Vector3(0, -180, 0));
}

