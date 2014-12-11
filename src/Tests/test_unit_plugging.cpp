#define BOOST_TEST_MODULE UnitPlugging
#include <boost/test/unit_test.hpp>
#include "Tests/UnitMock.hpp"
#include "UnitPlugging.hpp"

using namespace Synthetics;
using namespace Synthetics::Tests;

BOOST_AUTO_TEST_SUITE(UnitPluggingInstantiate)

BOOST_AUTO_TEST_CASE(test_instantiate_UnitPlugging) {
  UnitPlugging *plugging = new UnitPlugging(NULL, NULL, 0);
  BOOST_CHECK(plugging);
  delete plugging;
}

BOOST_AUTO_TEST_CASE(test_instantiate_UnitPlugging_0_faces) {
  UnitPlugging *plugging = new UnitPlugging(NULL, NULL, 0);
  BOOST_CHECK(plugging->getNoFaces() == 0);
  delete plugging;
}

BOOST_AUTO_TEST_CASE(test_instantiate_UnitPlugging_1_faces) {
  UnitPlugging *plugging = new UnitPlugging(NULL, NULL, 1);
  BOOST_CHECK(plugging->getNoFaces() == 1);
  delete plugging;
}

BOOST_AUTO_TEST_CASE(test_instantiate_UnitPlugging_n_faces) {
  UnitPlugging *plugging = new UnitPlugging(NULL, NULL, 78);
  BOOST_CHECK(plugging->getNoFaces() == 78);
  delete plugging;
}

BOOST_AUTO_TEST_SUITE_END()
