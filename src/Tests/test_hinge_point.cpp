//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestHingePoint
#include <boost/test/unit_test.hpp>
#include "HingePoint.hpp"
#include "Part.hpp"

using namespace Synthetics;
using namespace Polycode;

class PartMock : public Part {
  public:
    PartMock() {
    }
    ~PartMock() {}
    Polycode::Entity *getShape() { return NULL; }
};

//----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_hinge_point_instantiate) {
  HingePoint *hingePoint = new HingePoint(NULL, 0, 0);
  delete hingePoint;
}

class MyHingePointFixture {
  public:
    MyHingePointFixture() {
      part = new PartMock();
      hingePoint = new HingePoint(part, Vector3(1,2,3), Vector3(3,4,5));
    }

    Part *part;
    HingePoint *hingePoint;
};

BOOST_FIXTURE_TEST_SUITE(MyHingePoint, MyHingePointFixture)

  BOOST_AUTO_TEST_CASE(test_get_part) {
    BOOST_CHECK(hingePoint->getPart() == part);
  }

  BOOST_AUTO_TEST_CASE(test_get_pivot) {
    BOOST_CHECK(hingePoint->getPivot() == Vector3(1,2,3));
  }

  BOOST_AUTO_TEST_CASE(test_get_axis) {
    BOOST_CHECK(hingePoint->getAxis() == Vector3(3,4,5));
  }

BOOST_AUTO_TEST_SUITE_END()

