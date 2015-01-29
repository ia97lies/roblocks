//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestCompoundStore
#include <boost/test/unit_test.hpp>
#include "Exceptions.hpp"
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

  compound1.setId(0);
  compound2.setId(1);
  compound3.setId(2);

  store.insert(&compound1);
  store.insert(&compound2);
  store.insert(&compound3);
  BOOST_CHECK(store.get(0) == &compound1);
  BOOST_CHECK(store.get(1) == &compound2);
  BOOST_CHECK(store.get(2) == &compound3);
  BOOST_CHECK(store.get(3) == NULL);
}

BOOST_AUTO_TEST_CASE(test_compound_store_insert_component_with_existing_id) {
  CompoundStore store;
  Compound compound;

  store.insert(&compound);
  BOOST_CHECK_THROW(store.insert(0, &compound), AlreadyExistException);
}

BOOST_AUTO_TEST_CASE(test_compound_store_insert_component_with_existing_id_2) {
  CompoundStore store;
  Compound compound1;
  Compound compound2;

  compound1.setId(9999);
  compound2.setId(9999);

  store.insert(&compound1);
  BOOST_CHECK_THROW(store.insert(&compound2), AlreadyExistException);
}

BOOST_AUTO_TEST_CASE(test_compound_store_insert_remove_component) {
  CompoundStore store;
  Compound compound1;
  Compound compound2;
  Compound compound3;

  compound1.setId(0);
  compound2.setId(1);
  compound3.setId(2);

  store.insert(&compound1);
  store.insert(&compound2);
  store.insert(&compound3);
  store.remove(1);
  BOOST_CHECK(store.get(0) == &compound1);
  BOOST_CHECK(store.get(1) == NULL);
  BOOST_CHECK(store.get(2) == &compound3);
}

