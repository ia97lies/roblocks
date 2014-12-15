#define BOOST_TEST_MODULE UnitPlugging
#include <boost/test/unit_test.hpp>

#include "Unit/Entity.hpp"

using namespace Synthetics;

BOOST_AUTO_TEST_CASE(test_creat_destroy_entity) {
  Unit::Entity parent(0);
}

BOOST_AUTO_TEST_CASE(test_add_a_NULL_Unit) {
  Unit::Entity *parent = new Unit::Entity(1);
  parent->add(NULL);
  BOOST_CHECK(parent->get(0) == NULL);
}

BOOST_AUTO_TEST_CASE(test_add_a_entity) {
  Unit::Entity *parent = new Unit::Entity(1);
  Unit::Entity *entity = new Unit::Entity(1);
  parent->add(entity);
  BOOST_CHECK(parent->get(0) == entity);
  BOOST_CHECK(entity->get(0) == parent);
}

BOOST_AUTO_TEST_CASE(test_add_two_UnitEntites) {
  Unit::Entity parent(2);
  Unit::Entity *entity[2];
  for (int i = 0; i < 2; i++) {
    entity[i] = new Unit::Entity(1);
    parent.setActiveFace(i);
    parent.add(entity[i]);
  }
  for (int i = 0; i < 2; i++) {
    BOOST_CHECK(parent.get(i) == entity[i]);
    BOOST_CHECK(entity[i]->get(0) == &parent);
  }
}

BOOST_AUTO_TEST_CASE(test_add_remove_UnitEntites) {
  Unit::Entity parent(2);
  Unit::Entity *entity[2];
  for (int i = 0; i < 2; i++) {
    entity[i] = new Unit::Entity(1);
    parent.setActiveFace(i);
    parent.add(entity[i]);
  }
  Unit::Entity *removed = parent.remove(0);
  BOOST_CHECK(parent.get(0) == NULL);
  BOOST_CHECK(removed == entity[0]);
  BOOST_CHECK(parent.get(1) == entity[1]);
  BOOST_CHECK(entity[1]->get(0) == &parent);
}

BOOST_AUTO_TEST_CASE(test_add_remove_UnitEntites_by_entity_pointer) {
  Unit::Entity parent(2);
  Unit::Entity *entity[2];
  for (int i = 0; i < 2; i++) {
    entity[i] = new Unit::Entity(1);
    parent.setActiveFace(i);
    parent.add(entity[i]);
  }
  Unit::Entity *removed = parent.remove(entity[1]);
  BOOST_CHECK(parent.get(0) == entity[0]);
  BOOST_CHECK(entity[0]->get(0) == &parent);
  BOOST_CHECK(removed == entity[1]);
  BOOST_CHECK(parent.get(1) == NULL);
}

BOOST_AUTO_TEST_CASE(test_add_destroy_UnitEntites) {
  Unit::Entity parent(1);
  Unit::Entity *entity = new Unit::Entity(1);
  parent.add(entity);

  delete entity;
  BOOST_CHECK(parent.get(0) == NULL);
}

BOOST_AUTO_TEST_CASE(test_set_active_face_out_of_bound) {
  Unit::Entity entity(1);
  BOOST_CHECK_THROW(entity.setActiveFace(1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_get_out_of_bound_Unit) {
  Unit::Entity entity1(1);
  Unit::Entity *entity2= new Unit::Entity(1);
  entity1.add(entity2);
  BOOST_CHECK_THROW(entity1.get(1), std::out_of_range)
}

BOOST_AUTO_TEST_CASE(test_get_no_childs) {
  Unit::Entity entity1(10);
  Unit::Entity *entity[3];
  for (int i = 0; i < 3; i++) {
    entity[i]= new Unit::Entity(1);
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
  Unit::Entity entity(1);
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

BOOST_AUTO_TEST_CASE(test_add_remove_notify_entity) {
  Unit::Entity parent(1);
  Unit::Entity entity(1);
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

BOOST_AUTO_TEST_CASE(test_add_remove_reference_notify_entity) {
  Unit::Entity parent(1);
  Unit::Entity entity(1);
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

