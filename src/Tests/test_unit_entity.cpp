#define BOOST_TEST_MODULE UnitPlugging
#include <boost/test/unit_test.hpp>

#include "UnitEntity.hpp"

using namespace Polycode;
using namespace Synthetics;

class UnitMock : public Unit {
  public:
    UnitMock() {};
    virtual ~UnitMock() {};

    virtual void init() {};
    virtual UnitPlugging *getPlugging() { return NULL; };
    virtual void setActive(bool on) {}; 
    virtual Polycode::ScenePrimitive * getPolycodeObject() { return NULL; };
    virtual void handleEvent(Polycode::Event *event) {};
};

BOOST_AUTO_TEST_CASE(test_creat_destroy_UnitEntity) {
  UnitEntity entity(0);
}

BOOST_AUTO_TEST_CASE(test_add_one_Unit) {
  UnitEntity entity(1);
  entity.addUnit(NULL);
  BOOST_CHECK(entity.getUnit(0) == NULL);
}

BOOST_AUTO_TEST_CASE(test_add_a_NULL_Unit) {
  UnitEntity entity(1);
  entity.addUnit(NULL);
  BOOST_CHECK(entity.getUnit(0) == NULL);
}

BOOST_AUTO_TEST_CASE(test_add_a_Unit) {
  UnitEntity entity(1);
  UnitMock *unit = new UnitMock();
  entity.addUnit(unit);
  BOOST_CHECK(entity.getUnit(0) == unit);
}

BOOST_AUTO_TEST_CASE(test_add_two_Units) {
  UnitEntity entity(2);
  UnitMock *unit1 = new UnitMock();
  UnitMock *unit2 = new UnitMock();
  entity.setActiveFace(0);
  entity.addUnit(unit1);
  entity.setActiveFace(1);
  entity.addUnit(unit2);
  BOOST_CHECK(entity.getUnit(0) == unit1);
  BOOST_CHECK(entity.getUnit(1) == unit2);
}

BOOST_AUTO_TEST_CASE(test_set_active_face_out_of_bound) {
  UnitEntity entity(1);
  BOOST_CHECK_THROW(entity.setActiveFace(1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_get_out_of_bound_Unit) {
  UnitEntity entity(1);
  UnitMock *unit = new UnitMock();
  entity.addUnit(unit);
  BOOST_CHECK_THROW(entity.getUnit(1), std::out_of_range)
}

BOOST_AUTO_TEST_CASE(test_get_no_childs) {
  UnitEntity entity(10);
  UnitMock *unit = new UnitMock();
  for (int i = 3; i < 10; i += 3) {
    entity.setActiveFace(i);
    entity.addUnit(unit);
  }
  BOOST_CHECK(entity.getNoChilds() == 3);
}

