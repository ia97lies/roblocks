//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestCompoundStore
#include <boost/test/unit_test.hpp>
#include "Compound.hpp"
#include "CompoundStore.hpp"

using namespace Synthetics;

BOOST_AUTO_TEST_CASE(test_compound_store_instantiate) {
  CompoundStore store; 
}

BOOST_AUTO_TEST_CASE(test_compound_store_insert_first_compound) {
  CompoundStore store;
  Compound compound;

  store.insert(&compound);
  BOOST_CHECK(compound.getId() == 0);
  BOOST_CHECK(store.get(0) == &compound);
}

BOOST_AUTO_TEST_CASE(test_compound_store_get_not_existing_compound) {
  CompoundStore store;
  BOOST_CHECK(store.get(0) == NULL);
}
