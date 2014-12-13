#define BOOST_TEST_MODULE UnitPlugging
#include <boost/test/unit_test.hpp>

#include "UnitEntity.hpp"

using namespace Synthetics;

BOOST_AUTO_TEST_CASE(test_creat_destroy_UnitEntity) {
  UnitEntity parent(0);
}

BOOST_AUTO_TEST_CASE(test_add_a_NULL_Unit) {
  UnitEntity *parent = new UnitEntity(1);
  parent->add(NULL);
  BOOST_CHECK(parent->get(0) == NULL);
}

BOOST_AUTO_TEST_CASE(test_add_a_UnitEntity) {
  UnitEntity *parent = new UnitEntity(1);
  UnitEntity *entity = new UnitEntity(1);
  parent->add(entity);
  BOOST_CHECK(parent->get(0) == entity);
  BOOST_CHECK(entity->get(0) == parent);
}

BOOST_AUTO_TEST_CASE(test_add_two_UnitEntites) {
  UnitEntity parent(2);
  UnitEntity *entity[2];
  for (int i = 0; i < 2; i++) {
    entity[i] = new UnitEntity(1);
    parent.setActiveFace(i);
    parent.add(entity[i]);
  }
  for (int i = 0; i < 2; i++) {
    BOOST_CHECK(parent.get(i) == entity[i]);
    BOOST_CHECK(entity[i]->get(0) == &parent);
  }
}

BOOST_AUTO_TEST_CASE(test_add_remove_UnitEntites) {
  UnitEntity parent(2);
  UnitEntity *entity[2];
  for (int i = 0; i < 2; i++) {
    entity[i] = new UnitEntity(1);
    parent.setActiveFace(i);
    parent.add(entity[i]);
  }
  UnitEntity *removed = parent.remove(0);
  BOOST_CHECK(parent.get(0) == NULL);
  BOOST_CHECK(removed == entity[0]);
  BOOST_CHECK(parent.get(1) == entity[1]);
  BOOST_CHECK(entity[1]->get(0) == &parent);
}

BOOST_AUTO_TEST_CASE(test_add_remove_UnitEntites_by_UnitEntity_pointer) {
  UnitEntity parent(2);
  UnitEntity *entity[2];
  for (int i = 0; i < 2; i++) {
    entity[i] = new UnitEntity(1);
    parent.setActiveFace(i);
    parent.add(entity[i]);
  }
  UnitEntity *removed = parent.remove(entity[1]);
  BOOST_CHECK(parent.get(0) == entity[0]);
  BOOST_CHECK(entity[0]->get(0) == &parent);
  BOOST_CHECK(removed == entity[1]);
  BOOST_CHECK(parent.get(1) == NULL);
}

BOOST_AUTO_TEST_CASE(test_add_destroy_UnitEntites) {
  UnitEntity parent(1);
  UnitEntity *entity = new UnitEntity(1);
  parent.add(entity);

  delete entity;
  BOOST_CHECK(parent.get(0) == NULL);
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

class Mockup {
  public:
    Mockup() {gotRemoveEvent = false;};
    ~Mockup() {};
    bool gotRemoveEvent;
};

BOOST_AUTO_TEST_CASE(test_set_get_user_data) {
  UnitEntity entity(1);
  Mockup *mockup = new Mockup();
  entity.setUserData(mockup, NULL);
  Mockup *ref = (Mockup *)entity.getUserData();
  BOOST_CHECK(mockup == ref);
}

void mockupNotify(void *data, void *parentData, int event) {
  Mockup *mockup = (Mockup *)data;
  mockup->gotRemoveEvent = true;
  Mockup *parentMockup = (Mockup *)parentData;
  parentMockup->gotRemoveEvent = true;
}

BOOST_AUTO_TEST_CASE(test_add_remove_notify_UnitEntity) {
  UnitEntity parent(1);
  UnitEntity entity(1);
  Mockup *parentMockup = new Mockup();
  BOOST_CHECK(!parentMockup->gotRemoveEvent);
  parent.setUserData(parentMockup, mockupNotify);
  Mockup *mockup = new Mockup();
  BOOST_CHECK(!mockup->gotRemoveEvent);
  entity.setUserData(mockup, mockupNotify);
  parent.add(&entity);
  parent.remove(0);
  BOOST_CHECK(parentMockup->gotRemoveEvent);
  BOOST_CHECK(mockup->gotRemoveEvent);
}

BOOST_AUTO_TEST_CASE(test_add_remove_reference_notify_UnitEntity) {
  UnitEntity parent(1);
  UnitEntity entity(1);
  Mockup *parentMockup = new Mockup();
  BOOST_CHECK(!parentMockup->gotRemoveEvent);
  parent.setUserData(parentMockup, mockupNotify);
  Mockup *mockup = new Mockup();
  BOOST_CHECK(!mockup->gotRemoveEvent);
  entity.setUserData(mockup, mockupNotify);
  parent.add(&entity);
  parent.remove(&entity);
  BOOST_CHECK(parentMockup->gotRemoveEvent);
  BOOST_CHECK(mockup->gotRemoveEvent);
}

