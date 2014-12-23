//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE LoadCompounds
#include <boost/test/unit_test.hpp>
#include "Compound.hpp"

using namespace Synthetics;

class Mock : public Compound {
  public:
    Mock() {}
    ~Mock() {}
};

BOOST_AUTO_TEST_CASE(test_compound_add_one) {
  Mock *mock = new Mock();
  Compound *compound = new Compound();
  
  compound->add(mock);
  BOOST_CHECK(compound->getNoEntries() == 1);
  BOOST_CHECK(compound->get(0) == mock);
}

BOOST_AUTO_TEST_CASE(test_compound_add_manny) {
  Mock *mock = new Mock();
  Compound *compound = new Compound();
  
  compound->add(mock);
  compound->add(mock);
  compound->add(mock);
  BOOST_CHECK(compound->getNoEntries() == 3);
  BOOST_CHECK(compound->get(0) == mock);
  BOOST_CHECK(compound->get(1) == mock);
  BOOST_CHECK(compound->get(2) == mock);
}

BOOST_AUTO_TEST_CASE(test_compound_add_one_remove_one) {
  Mock *mock = new Mock();
  Compound *compound = new Compound();
  
  compound->add(mock);
  BOOST_CHECK(compound->getNoEntries() == 1);
  BOOST_CHECK(compound->get(0) == mock);
  compound->remove(0);
  BOOST_CHECK(compound->getNoEntries() == 0);
  BOOST_CHECK(compound->get(0) == NULL);
}

BOOST_AUTO_TEST_CASE(test_compound_add_many_remove_one_add_one) {
  Mock *mock = new Mock();
  Compound *compound = new Compound();
  
  compound->add(mock);
  compound->add(mock);
  compound->add(mock);
  BOOST_CHECK(compound->getNoEntries() == 3);
  compound->remove(1);
  BOOST_CHECK(compound->getNoEntries() == 2);
  BOOST_CHECK(compound->get(0) == mock);
  BOOST_CHECK(compound->get(1) == NULL);
  BOOST_CHECK(compound->get(2) == mock);
}

BOOST_AUTO_TEST_CASE(test_compound_add_many_replace_one) {
  Mock *mock = new Mock();
  Mock *mock2 = new Mock();
  Compound *compound = new Compound();
  
  compound->add(mock);
  compound->add(mock);
  compound->add(mock);
  BOOST_CHECK(compound->getNoEntries() == 3);
  compound->add(1, mock2);
  BOOST_CHECK(compound->getNoEntries() == 3);
  BOOST_CHECK(compound->get(0) == mock);
  BOOST_CHECK(compound->get(1) == mock2);
  BOOST_CHECK(compound->get(2) == mock);
}

BOOST_AUTO_TEST_CASE(test_compound_add_many_remove_two_size_remain) {
  Mock *mock = new Mock();
  Compound *compound = new Compound();
  
  compound->add(mock);
  compound->add(mock);
  compound->add(mock);
  BOOST_CHECK(compound->size() == 3);
  compound->remove(0);
  BOOST_CHECK(compound->size() == 3);
  compound->remove(2);
  BOOST_CHECK(compound->size() == 3);
}

