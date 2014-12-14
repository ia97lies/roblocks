#define BOOST_TEST_MODULE UnitPlugging
#include <stdio.h>
#include <boost/test/unit_test.hpp>

#include "UnitPosition.hpp"

using namespace Polycode;
using namespace Synthetics;

BOOST_AUTO_TEST_CASE(test_instantiate_UnitPosition) {
  UnitPosition pos(Vector3(1, 2, 3));
}

BOOST_AUTO_TEST_CASE(test_get_orientation) {
  UnitPosition pos(Vector3(1, 2, 3));
  BOOST_CHECK(pos.getOrientation() == Vector3(1, 2, 3));
}

BOOST_AUTO_TEST_CASE(test_get_orientation_versus_orientation_rotation) {
  UnitPosition pos1(Vector3(1, 0, 0));
  UnitPosition pos2(Vector3(-1, 0, 0));
  BOOST_CHECK(pos1.getRotation(&pos2) == Vector3(0, 0, 0));
}

BOOST_AUTO_TEST_CASE(test_get_orientation_same_orientation_rotation) {
  UnitPosition pos1(Vector3(1, 0, 0));
  UnitPosition pos2(Vector3(1, 0, 0));
  BOOST_CHECK(pos1.getRotation(&pos2) == Vector3(0, -180, 0));
}

