//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestRobot
#include <boost/test/unit_test.hpp>
#include "PolycodeFacade.hpp"
#include "Plug.hpp"
#include "Robot.hpp"

using namespace Synthetics;
using namespace Polycode;

class PolycodeMock : public PolycodeFacade {
  public:
    PolycodeMock() : PolycodeFacade(NULL, NULL) {}
    ~PolycodeMock() {}
 
    virtual void addEntity(Polycode::Entity *entity) { addedEntity = entity; }
    virtual void trackCollisionEntity(Polycode::Entity *entity) { trackedEntity = entity; }
    virtual void removeEntity(Polycode::Entity *entity) { removedEntity = entity; }

    Polycode::Entity *addedEntity;
    Polycode::Entity *trackedEntity;
    Polycode::Entity *removedEntity;
};

class PlugMock : public Plug {
  public:
    PlugMock(Vector3 position, Vector3 rotation) : Plug(position, rotation) { 
      isActivated = false; 
    }
    virtual void activate(bool on) {
      isActivated = on;
    }
    bool isActivated;
};

class PartMock : public Part {
  public:
    PartMock() {
      m_shape = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 1, 1);
    }
    ~PartMock() {}
    Polycode::Entity *getShape() { return m_shape; }
  private:
    Polycode::Entity *m_shape;
};

class ComponentMock : public Component {
  public:
    ComponentMock(bool *deleted) { 
      m_deleted = deleted; 
      m_part = new PartMock();
      m_plug[0] = new PlugMock(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_plug[0]->setParent(this);
      m_part->addPlug(m_plug[0]);
      m_plug[1] = new PlugMock(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_plug[1]->setParent(this);
      m_part->addPlug(m_plug[1]);
    }
    ~ComponentMock() { *m_deleted = true; }

    int getNoParts() { return 1; }
    Part *getPart(int i) { return m_part; }
    void enable(bool on) {}
    void update(Plug *sendingPlug, Polycode::Vector3 delta) {}
    PlugMock *getMyPlug(int i) { return m_plug[i]; }

  private:
    bool *m_deleted;
    Part *m_part;
    PlugMock *m_plug[2];
};

BOOST_AUTO_TEST_CASE(test_robot_instantiate) {
  PolycodeMock *polycodeMock = new PolycodeMock();
  Robot *robot = new Robot(polycodeMock);
  delete robot;
  delete polycodeMock;
}

BOOST_AUTO_TEST_CASE(test_robot_add_one_component) {
  bool deleted = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  ComponentMock *componentMock = new ComponentMock(&deleted);
  Robot *robot = new Robot(polycodeMock);

  robot->add(componentMock);
  BOOST_CHECK(deleted == false);
}

BOOST_AUTO_TEST_CASE(test_robot_is_empty) {
  PolycodeMock *polycodeMock = new PolycodeMock();
  Robot *robot = new Robot(polycodeMock);
  BOOST_CHECK(robot->isEmpty());
}

BOOST_AUTO_TEST_CASE(test_robot_is_not_empty) {
  bool deleted = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  ComponentMock *componentMock = new ComponentMock(&deleted);
  Robot *robot = new Robot(polycodeMock);
  robot->add(componentMock);
  BOOST_CHECK(!robot->isEmpty());
}

// this cores if m_mother is not checked to NULL
BOOST_AUTO_TEST_CASE(test_robot_activated_plug_no_component) {
  bool dummy = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  Robot *robot = new Robot(polycodeMock);
  ComponentMock *componentMock = new ComponentMock(&dummy);
  robot->activate(componentMock->getMyPlug(0)->getShape());
}

BOOST_AUTO_TEST_CASE(test_robot_add_one_component_add_second_no_activated_plug) {
  bool deleted = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  ComponentMock *componentMock = new ComponentMock(&deleted);
  Robot *robot = new Robot(polycodeMock);

  robot->add(componentMock);
  BOOST_CHECK(deleted == false);

  // first element is set, no plug is activated
  componentMock = new ComponentMock(&deleted);
  robot->add(componentMock);
  BOOST_CHECK(deleted == true);
}

BOOST_AUTO_TEST_CASE(test_robot_activate_plug_one_level) {
  bool deleted = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  ComponentMock *componentMock = new ComponentMock(&deleted);
  Robot *robot = new Robot(polycodeMock);

  BOOST_CHECK(componentMock->getMyPlug(0) != NULL);

  robot->add(componentMock);
  robot->activate(componentMock->getMyPlug(0)->getShape());

  BOOST_CHECK(componentMock->getMyPlug(0)->isActivated);
  BOOST_CHECK(!componentMock->getMyPlug(1)->isActivated);

  robot->activate(componentMock->getMyPlug(1)->getShape());

  BOOST_CHECK(!componentMock->getMyPlug(0)->isActivated);
  BOOST_CHECK(componentMock->getMyPlug(1)->isActivated);
}

BOOST_AUTO_TEST_CASE(test_robot_activate_plug_one_more_level) {
  bool deleted = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  ComponentMock *componentMock = new ComponentMock(&deleted);
  Robot *robot = new Robot(polycodeMock);
  robot->add(componentMock);
  robot->activate(componentMock->getMyPlug(0)->getShape());
  componentMock = new ComponentMock(&deleted);
  robot->place(componentMock);
  robot->add();

  robot->activate(componentMock->getMyPlug(0)->getShape());
  BOOST_CHECK(componentMock->getMyPlug(0)->isActivated);
}

BOOST_AUTO_TEST_CASE(test_robot_activate_plug_more_level) {
  bool deleted = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  ComponentMock *componentMock = new ComponentMock(&deleted);
  Robot *robot = new Robot(polycodeMock);
  robot->add(componentMock);
  robot->activate(componentMock->getMyPlug(0)->getShape());
  componentMock = new ComponentMock(&deleted);
  robot->place(componentMock);
  robot->add();
  robot->activate(componentMock->getMyPlug(0)->getShape());
  componentMock = new ComponentMock(&deleted);
  robot->place(componentMock);
  robot->add();
  robot->activate(componentMock->getMyPlug(0)->getShape());

  BOOST_CHECK(componentMock->getMyPlug(0)->isActivated);
}

BOOST_AUTO_TEST_CASE(test_robot_get_activate_plug) {
  bool deleted = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  ComponentMock *componentMock = new ComponentMock(&deleted);
  Robot *robot = new Robot(polycodeMock);

  robot->add(componentMock);
  robot->activate(componentMock->getMyPlug(0)->getShape());

  BOOST_CHECK(robot->getActivePlug() == componentMock->getMyPlug(0));
}

BOOST_AUTO_TEST_CASE(test_robot_add_one_component_add_second_to_activated_plug) {
  bool deleted = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  ComponentMock *componentMock = new ComponentMock(&deleted);
  Robot *robot = new Robot(polycodeMock);

  robot->add(componentMock);
  BOOST_CHECK(deleted == false);

  robot->activate(componentMock->getMyPlug(0)->getShape());
  componentMock = new ComponentMock(&deleted);
  robot->place(componentMock);
  robot->add();
  BOOST_CHECK(deleted == false);
}

BOOST_AUTO_TEST_CASE(test_robot_remove_component) {
  bool deleted = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  Robot *robot = new Robot(polycodeMock);
  ComponentMock *componentMock = new ComponentMock(&deleted);

  robot->add(componentMock);
  robot->activate(componentMock->getMyPlug(0)->getShape());
  deleted = false;
  ComponentMock *componentMock2 = new ComponentMock(&deleted);
  robot->place(componentMock2);
  robot->add();

  robot->activate(componentMock2->getMyPlug(0)->getShape());
  robot->remove();
  BOOST_CHECK(deleted == true);
  BOOST_CHECK(componentMock->getMyPlug(0)->getConnectedPlug() == NULL);
  // TODO: write tests for destruct component (all parts get destructed?)
}

BOOST_AUTO_TEST_CASE(test_robot_remove_component_with_more_parents) {
  bool dummy = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  ComponentMock *mother= new ComponentMock(&dummy);
  Robot *robot = new Robot(polycodeMock);

  robot->add(mother);
  robot->activate(mother->getMyPlug(0)->getShape());
  ComponentMock *componentMock1 = new ComponentMock(&dummy);
  robot->place(componentMock1);
  robot->add();
  robot->activate(mother->getMyPlug(1)->getShape());
  ComponentMock *componentMock2 = new ComponentMock(&dummy);
  robot->place(componentMock2);
  robot->add();

  bool deleted = false;
  robot->activate(componentMock1->getMyPlug(0)->getShape());
  ComponentMock *componentMock3 = new ComponentMock(&deleted);
  robot->place(componentMock3);
  robot->add();
  componentMock2->add(componentMock3);
  componentMock2->getMyPlug(0)->setConnectedPlug(componentMock3->getMyPlug(1));

  robot->activate(componentMock3->getMyPlug(0)->getShape());
  robot->remove();
  BOOST_CHECK(deleted == true);
  BOOST_CHECK(componentMock1->getMyPlug(0)->getConnectedPlug() == NULL);
  BOOST_CHECK(componentMock2->getMyPlug(0)->getConnectedPlug() == NULL);
  // TODO: write tests for destruct component (all parts get destructed?)
}

BOOST_AUTO_TEST_CASE(test_robot_remove_component_with_more_parents_2) {
  bool dummy = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  ComponentMock *mother= new ComponentMock(&dummy);
  Robot *robot = new Robot(polycodeMock);

  robot->add(mother);
  robot->activate(mother->getMyPlug(0)->getShape());
  ComponentMock *componentMock1 = new ComponentMock(&dummy);
  robot->place(componentMock1);
  robot->add();
  robot->activate(mother->getMyPlug(1)->getShape());
  ComponentMock *componentMock2 = new ComponentMock(&dummy);
  robot->place(componentMock2);
  robot->add();

  bool deleted = false;
  robot->activate(componentMock1->getMyPlug(0)->getShape());
  ComponentMock *componentMock3 = new ComponentMock(&deleted);
  robot->place(componentMock3);
  robot->add();
  componentMock2->add(componentMock3);
  componentMock2->getMyPlug(1)->setConnectedPlug(componentMock3->getMyPlug(1));

  robot->activate(componentMock3->getMyPlug(0)->getShape());
  robot->remove();
  BOOST_CHECK(deleted == true);
  BOOST_CHECK(componentMock1->getMyPlug(0)->getConnectedPlug() == NULL);
  BOOST_CHECK(componentMock2->getMyPlug(1)->getConnectedPlug() == NULL);
  // TODO: write tests for destruct component (all parts get destructed?)
}

BOOST_AUTO_TEST_CASE(test_robot_destruction_null_mother) {
  PolycodeMock *polycodeMock = new PolycodeMock();
  Robot *robot = new Robot(polycodeMock);
  delete robot;
}

BOOST_AUTO_TEST_CASE(test_robot_destruction_only_mother) {
  bool deleted = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  ComponentMock *mother= new ComponentMock(&deleted);
  Robot *robot = new Robot(polycodeMock);

  robot->add(mother);
  delete robot;
  BOOST_CHECK(deleted == true);
}

BOOST_AUTO_TEST_CASE(test_robot_destruction_mother_and_child) {
  bool deleted[2] = { false, false };
  PolycodeMock *polycodeMock = new PolycodeMock();
  Robot *robot = new Robot(polycodeMock);

  ComponentMock *mother= new ComponentMock(&deleted[0]);
  robot->add(mother);
  robot->activate(mother->getMyPlug(0)->getShape());
  ComponentMock *componentMock1 = new ComponentMock(&deleted[1]);
  robot->place(componentMock1);
  robot->add();

  delete robot;
  for (int i = 0; i < 2; i++) {
    BOOST_CHECK(deleted[i] == true);
  }
}

BOOST_AUTO_TEST_CASE(test_robot_destruction_mother_and_many_children) {
  bool deleted[5] = { false, false, false, false, false };
  PolycodeMock *polycodeMock = new PolycodeMock();
  Robot *robot = new Robot(polycodeMock);

  ComponentMock *mother= new ComponentMock(&deleted[0]);
  robot->add(mother);
  robot->activate(mother->getMyPlug(0)->getShape());
  ComponentMock *componentMock1 = new ComponentMock(&deleted[1]);
  robot->place(componentMock1);
  robot->add();
  robot->activate(mother->getMyPlug(1)->getShape());
  ComponentMock *componentMock2 = new ComponentMock(&deleted[2]);
  robot->place(componentMock2);
  robot->add();
  robot->activate(componentMock1->getMyPlug(0)->getShape());
  ComponentMock *componentMock3 = new ComponentMock(&deleted[3]);
  robot->place(componentMock3);
  robot->add();
  robot->activate(componentMock3->getMyPlug(0)->getShape());
  ComponentMock *componentMock4 = new ComponentMock(&deleted[4]);
  robot->place(componentMock4);
  robot->add();

  delete robot;
  for (int i = 0; i < 5; i++) {
    BOOST_CHECK(deleted[i] == true);
  }
}

