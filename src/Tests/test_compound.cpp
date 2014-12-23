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

BOOST_AUTO_TEST_CASE(test_load_compound) {
  Mock *mock = new Mock();
  Compound *compound = new Compound();
  
  compound->add(mock);
  BOOST_CHECK(compound->getNoEntries() == 1);
  BOOST_CHECK(compound->get(0) == mock);
}

