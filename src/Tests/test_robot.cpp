//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE Robot
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
    virtual void trackEntity(Polycode::Entity *entity) { trackedEntity = entity; }
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
      m_part->addPlug(m_plug[0]);
      m_plug[1] = new PlugMock(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_part->addPlug(m_plug[1]);
    }
    ~ComponentMock() { *m_deleted = true; }

    int getNoParts() { return 1; }
    Part *getPart(int i) { return m_part; }
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

BOOST_AUTO_TEST_CASE(test_robot_activate_plug) {
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

BOOST_AUTO_TEST_CASE(test_robot_add_one_component_add_second_to_activated_plug) {
  bool deleted = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  ComponentMock *componentMock = new ComponentMock(&deleted);
  Robot *robot = new Robot(polycodeMock);

  robot->add(componentMock);
  BOOST_CHECK(deleted == false);

  robot->activate(componentMock->getMyPlug(0)->getShape());
  componentMock = new ComponentMock(&deleted);
  robot->add(componentMock);
  BOOST_CHECK(deleted == false);
}

