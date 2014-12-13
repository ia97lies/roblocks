#define BOOST_TEST_MODULE UnitPlugging
#include <boost/test/unit_test.hpp>

#include "UnitPosition.hpp"

using namespace Polycode;
using namespace Synthetics;

BOOST_AUTO_TEST_CASE(test_instantiate_UnitPosition) {
  UnitPosition pos(Vector3(1, 2, 3), Vector3(3, 2, 1));
}

BOOST_AUTO_TEST_CASE(test_get_shift) {
  UnitPosition pos(Vector3(1, 2, 3), Vector3(3, 2, 1));
  BOOST_CHECK(pos.getShift() == Vector3(1, 2, 3));
}

