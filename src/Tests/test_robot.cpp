//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE Robot
#include <boost/test/unit_test.hpp>
#include "PolycodeFacade.hpp"
#include "Robot.hpp"

using namespace Synthetics;

class Mock : public PolycodeFacade {
  public:
    Mock() : PolycodeFacade(NULL, NULL) {}
    ~Mock() {}
 
    virtual void addEntity(Polycode::Entity *entity) {}
    virtual void trackEntity(Polycode::Entity *entity) {}
    virtual void removeEntity(Polycode::Entity *entity) {}
};

BOOST_AUTO_TEST_CASE(test_robot_instantiate) {
  Mock *mock = new Mock();
  Robot *robot = new Robot(mock);
  delete robot;
  delete mock;
}

