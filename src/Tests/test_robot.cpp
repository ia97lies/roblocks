//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE Robot
#include <boost/test/unit_test.hpp>
#include "PolycodeFacade.hpp"
#include "Robot.hpp"

using namespace Synthetics;

class PolycodeMock : public PolycodeFacade {
  public:
    PolycodeMock() : PolycodeFacade(NULL, NULL) {}
    ~PolycodeMock() {}
 
    virtual void addEntity(Polycode::Entity *entity) {}
    virtual void trackEntity(Polycode::Entity *entity) {}
    virtual void removeEntity(Polycode::Entity *entity) {}
};

class ComponentMock : public Component {
  public:
    ComponentMock(bool *deleted) { m_deleted = deleted; }
    ~ComponentMock() { *m_deleted = true; }

    int getNoParts() { return 0; }
    Part *getPart(int i) { return NULL; }
  private:
    bool *m_deleted;
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

