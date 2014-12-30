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
      isOn = false; 
    }
    virtual void activate(bool on) {
      isOn = on;
    }
    bool isOn;
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
      m_plug = new PlugMock(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_part->addPlug(m_plug);
    }
    ~ComponentMock() { *m_deleted = true; }

    int getNoParts() { return 1; }
    Part *getPart(int i) { return m_part; }
    PlugMock *getMyPlug() { return m_plug; }
  private:
    bool *m_deleted;
    Part *m_part;
    PlugMock *m_plug;
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

  delete robot;
  delete polycodeMock;
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

  delete robot;
  delete polycodeMock;
}

BOOST_AUTO_TEST_CASE(test_robot_activate_plug) {
  bool deleted = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  ComponentMock *componentMock = new ComponentMock(&deleted);
  Robot *robot = new Robot(polycodeMock);
  PlugMock *plugMock = componentMock->getMyPlug();

  BOOST_CHECK(plugMock != NULL);

  robot->add(componentMock);
  robot->activate(plugMock->getShape());
}

