//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE LoadCompounds
#include <boost/test/unit_test.hpp>
#include "Component.hpp"

using namespace Synthetics;

class Mock : public Component {
  public:
    Mock() {}
    ~Mock() {}

    int getNoParts() { return 0; }
    Part *getPart(int i) { return NULL; }
  private:
};

BOOST_AUTO_TEST_CASE(test_component_instantiate) {
  Mock *mock = new Mock();
  delete mock;
}

