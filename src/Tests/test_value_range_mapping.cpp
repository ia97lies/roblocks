//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestValueRangeMapping
#include <boost/test/unit_test.hpp>
#include "ValueRangeMapping.hpp"

using namespace Synthetics;

BOOST_AUTO_TEST_CASE(test_value_range_mapping_instantiate) {
  ValueRangeMapping mapping(-90, 90, 0);
}

BOOST_AUTO_TEST_CASE(test_value_range_mapping_map_min) {
  ValueRangeMapping mapping(-90, 90, 0);
  BOOST_CHECK(mapping.value() == 0);
  BOOST_CHECK(mapping.map() == -90);
}

BOOST_AUTO_TEST_CASE(test_value_range_mapping_map_max) {
  ValueRangeMapping mapping(-90, 90, 100);
  BOOST_CHECK(mapping.value() == 100);
  BOOST_CHECK(mapping.map() == 90);
}

BOOST_AUTO_TEST_CASE(test_value_range_mapping_map_medium) {
  ValueRangeMapping mapping(-90, 90, 50);
  BOOST_CHECK(mapping.value() == 50);
  BOOST_CHECK(mapping.map() == 0);
}

BOOST_AUTO_TEST_CASE(test_value_range_clamp_max) {
  ValueRangeMapping mapping(-90, 90, 150);
  BOOST_CHECK(mapping.value() == 100);
  BOOST_CHECK(mapping.map() == 90);
}

BOOST_AUTO_TEST_CASE(test_value_range_clamp_min) {
  ValueRangeMapping mapping(-90, 90, -104);
  BOOST_CHECK(mapping.value() == 0);
  BOOST_CHECK(mapping.map() == -90);
}

