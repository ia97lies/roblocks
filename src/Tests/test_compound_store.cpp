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

BOOST_AUTO_TEST_CASE(test_compound_store_more_compound) {
  CompoundStore store;
  Compound compound1;
  Compound compound2;
  Compound compound3;

  store.insert(&compound1);
  store.insert(&compound2);
  store.insert(&compound3);
  BOOST_CHECK(compound1.getId() == 0);
  BOOST_CHECK(compound2.getId() == 1);
  BOOST_CHECK(compound3.getId() == 2);
  BOOST_CHECK(store.get(0) == &compound1);
  BOOST_CHECK(store.get(1) == &compound2);
  BOOST_CHECK(store.get(2) == &compound3);
  BOOST_CHECK(store.get(3) == NULL);
}
