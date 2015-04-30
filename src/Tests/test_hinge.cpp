//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestHingePoint
#include <boost/test/unit_test.hpp>
#include "HingePoint.hpp"
#include "Hinge.hpp"
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
BOOST_AUTO_TEST_CASE(test_hinge_instantiate) {
  Hinge *hinge = new Hinge(NULL, NULL);
  delete hinge;
}

class MyHingeFixture {
  public:
    MyHingeFixture() {
      part[0] = new PartMock();
      hingePoint[0] = new HingePoint(part[0], Vector3(1,2,3), Vector3(3,4,5));
      part[1] = new PartMock();
      hingePoint[1] = new HingePoint(part[1], Vector3(5,6,7), Vector3(7,8,9));
      hinge = new Hinge(hingePoint[0], hingePoint[1]);
    }

    Part *part[2];
    HingePoint *hingePoint[2];
    Hinge *hinge;
};

BOOST_FIXTURE_TEST_SUITE(MyHinge, MyHingeFixture)

  BOOST_AUTO_TEST_CASE(test_hinge_get_point1) {
    BOOST_CHECK(hinge->getPoint(0) == hingePoint[0]);
  }

  BOOST_AUTO_TEST_CASE(test_hinge_get_point2) {
    BOOST_CHECK(hinge->getPoint(1) == hingePoint[1]);
  }

  BOOST_AUTO_TEST_CASE(test_hinge_get_point_index_too_big) {
    BOOST_CHECK_THROW(hinge->getPoint(2), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(test_hinge_get_point_negative_index) {
    BOOST_CHECK_THROW(hinge->getPoint(-1), std::out_of_range);
  }

BOOST_AUTO_TEST_SUITE_END()

