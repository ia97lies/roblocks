#define BOOST_TEST_MODULE UnitPlugging
#include <boost/test/unit_test.hpp>

#include "UnitEntity.hpp"

using namespace Synthetics;

class Mockup {
  public:
    Mockup() {};
    ~Mockup() {};
};

BOOST_AUTO_TEST_CASE(test_creat_destroy_UnitEntity) {
  UnitEntity entity(0);
}

BOOST_AUTO_TEST_CASE(test_add_one_Unit) {
  UnitEntity entity(1);
  entity.add(NULL);
  BOOST_CHECK(entity.get(0) == NULL);
}

BOOST_AUTO_TEST_CASE(test_add_a_NULL_Unit) {
  UnitEntity entity(1);
  entity.add(NULL);
  BOOST_CHECK(entity.get(0) == NULL);
}

BOOST_AUTO_TEST_CASE(test_add_a_Unit) {
  UnitEntity entity1(1);
  UnitEntity *entity2 = new UnitEntity(1);
  entity1.add(entity2);
  BOOST_CHECK(entity1.get(0) == entity2);
}

BOOST_AUTO_TEST_CASE(test_add_two_UnitEntites) {
  UnitEntity entity1(2);
  UnitEntity *entity[2];
  for (int i = 0; i < 2; i++) {
    entity[i] = new UnitEntity(1);
    entity1.setActiveFace(i);
    entity1.add(entity[i]);
  }
  for (int i = 0; i < 2; i++) {
    BOOST_CHECK(entity1.get(i) == entity[i]);
  }
}

BOOST_AUTO_TEST_CASE(test_add_remove_UnitEntites) {
  UnitEntity entity1(2);
  UnitEntity *entity[2];
  for (int i = 0; i < 2; i++) {
    entity[i] = new UnitEntity(1);
    entity1.setActiveFace(i);
    entity1.add(entity[i]);
  }
  UnitEntity *removed = entity1.remove(0);
  BOOST_CHECK(entity1.get(0) == NULL);
  BOOST_CHECK(removed == entity[0]);
  BOOST_CHECK(entity1.get(1) == entity[1]);
}

BOOST_AUTO_TEST_CASE(test_add_remove_UnitEntites_by_UnitEntity_pointer) {
  UnitEntity entity1(2);
  UnitEntity *entity[2];
  for (int i = 0; i < 2; i++) {
    entity[i] = new UnitEntity(1);
    entity1.setActiveFace(i);
    entity1.add(entity[i]);
  }
  UnitEntity *removed = entity1.remove(entity[1]);
  BOOST_CHECK(entity1.get(0) == entity[0]);
  BOOST_CHECK(removed == entity[1]);
  BOOST_CHECK(entity1.get(1) == NULL);
}

BOOST_AUTO_TEST_CASE(test_set_active_face_out_of_bound) {
  UnitEntity entity(1);
  BOOST_CHECK_THROW(entity.setActiveFace(1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_get_out_of_bound_Unit) {
  UnitEntity entity1(1);
  UnitEntity *entity2= new UnitEntity(1);
  entity1.add(entity2);
  BOOST_CHECK_THROW(entity1.get(1), std::out_of_range)
}

BOOST_AUTO_TEST_CASE(test_get_no_childs) {
  UnitEntity entity1(10);
  UnitEntity *entity[3];
  for (int i = 0; i < 3; i++) {
    entity[i]= new UnitEntity(1);
    entity1.setActiveFace(i*3);
    entity1.add(entity[i]);
  }
  BOOST_CHECK(entity1.getNoChilds() == 3);
}

BOOST_AUTO_TEST_CASE(test_set_get_user_data) {
  UnitEntity entity(1);
  Mockup *mockup = new Mockup();
  entity.setUserData(mockup);
  Mockup *ref = (Mockup *)entity.getUserData();
  BOOST_CHECK(mockup == ref);
}

