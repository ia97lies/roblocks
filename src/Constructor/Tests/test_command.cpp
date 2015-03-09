//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestRobot
#include <boost/test/unit_test.hpp>
#include "PolycodeFacade.hpp"
#include "Plug.hpp"
#include "Constructor/CommandSetRoot.hpp"
#include "Constructor/CommandActivate.hpp"
#include "Constructor/CommandPlace.hpp"
#include "Constructor/Robot.hpp"

using namespace Synthetics;
using namespace Synthetics::Constructor;
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
      m_plug[0] = new Plug(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_plug[0]->setParent(this);
      m_part->addPlug(m_plug[0]);
      m_plug[1] = new Plug(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_plug[1]->setParent(this);
      m_part->addPlug(m_plug[1]);
    }
    ~ComponentMock() { *m_deleted = true; }

    int getNoParts() { return 1; }
    Part *getPart(int i) { return m_part; }
    void enable(bool on) {}
    void update(Plug *sendingPlug, Polycode::Vector3 delta) {}
    Plug *getMyPlug(int i) { return m_plug[i]; }

  private:
    bool *m_deleted;
    Part *m_part;
    Plug *m_plug[2];
};

BOOST_AUTO_TEST_CASE(test_command_set_root_execute) {
  bool dummy = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  Robot *robot = new Robot(polycodeMock);
  ComponentMock *component = new ComponentMock(&dummy);
  CommandSetRoot *command = new CommandSetRoot(robot, component);
  command->execute();
  BOOST_CHECK(!robot->isEmpty());
}

BOOST_AUTO_TEST_CASE(test_command_set_root_undo) {
  bool dummy = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  Robot *robot = new Robot(polycodeMock);
  ComponentMock *component = new ComponentMock(&dummy);
  CommandSetRoot *command = new CommandSetRoot(robot, component);
  command->execute();
  command->undo();
  BOOST_CHECK(robot->isEmpty());
}

BOOST_AUTO_TEST_CASE(test_command_activate_execute) {
  bool dummy = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  Robot *robot = new Robot(polycodeMock);
  ComponentMock *component = new ComponentMock(&dummy);
  robot->setRoot(component);
  CommandActivate *command = new CommandActivate(robot, component->getMyPlug(0));
  command->execute();
  BOOST_CHECK(component->getMyPlug(0)->isActive());
}

BOOST_AUTO_TEST_CASE(test_command_activate_undo) {
  bool dummy = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  Robot *robot = new Robot(polycodeMock);
  ComponentMock *component = new ComponentMock(&dummy);
  robot->setRoot(component);
  robot->activate(component->getMyPlug(0)->getShape());
  CommandActivate *command = new CommandActivate(robot, component->getMyPlug(1));
  command->execute();
  command->undo();
  BOOST_CHECK(component->getMyPlug(0)->isActive());
  BOOST_CHECK(!component->getMyPlug(1)->isActive());
}

BOOST_AUTO_TEST_CASE(test_command_activate_undo_previous_plug_not_active) {
  bool dummy = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  Robot *robot = new Robot(polycodeMock);
  ComponentMock *component = new ComponentMock(&dummy);
  robot->setRoot(component);
  CommandActivate *command = new CommandActivate(robot, component->getMyPlug(1));
  command->execute();
  command->undo();
  // currently if non was active before we just do not touch anything
  // TODO: Extend robot to be able to deactivate a given plug constistent
  BOOST_CHECK(!component->getMyPlug(0)->isActive());
  BOOST_CHECK(component->getMyPlug(1)->isActive());
}

BOOST_AUTO_TEST_CASE(test_command_place_execute) {
  bool dummy = false;
  PolycodeMock *polycodeMock = new PolycodeMock();
  Robot *robot = new Robot(polycodeMock);
  ComponentMock *component1 = new ComponentMock(&dummy);
  robot->setRoot(component1);
  robot->activate(component1->getMyPlug(0)->getShape());
  ComponentMock *component2 = new ComponentMock(&dummy);
  CommandPlace *command = new CommandPlace(robot, component2);
  command->execute();
  BOOST_CHECK(component2->getPart(0)->getPlug(0)->isActive());
}

