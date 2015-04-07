//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestConstructorCommands
#include <boost/test/unit_test.hpp>
#include "PolycodeFacade.hpp"
#include "Plug.hpp"
#include "Components/Factory.hpp"
#include "Constructor/CommandSetRoot.hpp"
#include "Constructor/CommandActivate.hpp"
#include "Constructor/CommandPlace.hpp"
#include "Constructor/CommandRotateInPlace.hpp"
#include "Constructor/CommandAdd.hpp"
#include "Constructor/CommandRemove.hpp"
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
    ComponentMock(bool *deleted = NULL) { 
      m_deleted = deleted;
      m_part = new PartMock();
      m_plug[0] = new Plug(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_plug[0]->setParent(this);
      m_part->addPlug(m_plug[0]);
      m_plug[1] = new Plug(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_plug[1]->setParent(this);
      m_part->addPlug(m_plug[1]);
    }

    ~ComponentMock() { if (m_deleted != NULL) *m_deleted = true; }

    std::string getName() { return "My.Mock"; }
    Part *getPart(int i) { return m_part; }
    int getNoParts() { return 1; }
    void enable(bool on) {}
    void update(Plug *sendingPlug, Polycode::Vector3 delta) {}
    Plug *getMyPlug(int i) { return m_plug[i]; }

  private:
    bool *m_deleted;
    Part *m_part;
    Plug *m_plug[2];
};

Component *MockCreator(Polycode::PhysicsScene *scene) {
  return new ComponentMock();
}


//----------------------------------------------------------------------------
class SetRootFixture {
  public:
    SetRootFixture() {
      deleted = false;
      Components::Factory::get()->addCreator("My.Mock", MockCreator);
      PolycodeMock * polycodeMock = new PolycodeMock();
      robot = new Robot(polycodeMock);
      component = new ComponentMock(&deleted);
    }

    bool deleted;
    Robot *robot;
    ComponentMock *component;
};

BOOST_FIXTURE_TEST_SUITE(SetRoot, SetRootFixture)

  BOOST_AUTO_TEST_CASE(test_command_set_root_execute_always_true) {
    CommandSetRoot *command = new CommandSetRoot(robot, component);
    BOOST_CHECK(command->execute());
  }

  BOOST_AUTO_TEST_CASE(test_command_set_root_execute) {
    CommandSetRoot *command = new CommandSetRoot(robot, component);
    command->execute();
    BOOST_CHECK(!robot->isEmpty());
  }

  BOOST_AUTO_TEST_CASE(test_command_set_root_undo) {
    CommandSetRoot *command = new CommandSetRoot(robot, component);
    command->execute();
    command->undo();
    BOOST_CHECK(robot->isEmpty());
  }

  BOOST_AUTO_TEST_CASE(test_command_set_root_redo) {
    CommandSetRoot *command = new CommandSetRoot(robot, component);
    command->execute();
    command->undo();
    command->execute();
    BOOST_CHECK(!robot->isEmpty());
  }

  BOOST_AUTO_TEST_CASE(test_command_set_root_redo_no_active_plug) {
    CommandSetRoot *command = new CommandSetRoot(robot, component);
    command->execute();
    command->undo();
    command->execute();
    BOOST_CHECK(!component->getMyPlug(0)->isActive());
    BOOST_CHECK(!component->getMyPlug(1)->isActive());
  }

  BOOST_AUTO_TEST_CASE(test_command_set_root_execute_command_destroy) {
    CommandSetRoot *command = new CommandSetRoot(robot, component);
    command->execute();
    delete command;
    BOOST_CHECK(!deleted);
  }

  BOOST_AUTO_TEST_CASE(test_command_set_root_undo_command_destroy) {
    CommandSetRoot *command = new CommandSetRoot(robot, component);
    command->execute();
    command->undo();
    delete command;
    BOOST_CHECK(deleted);
  }

BOOST_AUTO_TEST_SUITE_END()


//----------------------------------------------------------------------------
class ActivateFixture {
  public:
    ActivateFixture() {
      polycodeMock = new PolycodeMock();
      robot = new Robot(polycodeMock);
      component = new ComponentMock();
      robot->setRoot(component);
      robot->activate(component->getMyPlug(0)->getShape());
    }

    PolycodeMock *polycodeMock;
    Robot *robot;
    ComponentMock *component;
};

BOOST_FIXTURE_TEST_SUITE(Activate, ActivateFixture)

  BOOST_AUTO_TEST_CASE(test_command_activate_execute_always_true) {
    CommandActivate *command = new CommandActivate(robot, component->getMyPlug(1)->getShape());
    BOOST_CHECK(command->execute());
  }

  BOOST_AUTO_TEST_CASE(test_command_activate_execute) {
    CommandActivate *command = new CommandActivate(robot, component->getMyPlug(1)->getShape());
    command->execute();
    BOOST_CHECK(component->getMyPlug(1)->isActive());
  }

  BOOST_AUTO_TEST_CASE(test_command_activate_undo) {
    CommandActivate *command = new CommandActivate(robot, component->getMyPlug(1)->getShape());
    command->execute();
    command->undo();
    BOOST_CHECK(component->getMyPlug(0)->isActive());
    BOOST_CHECK(!component->getMyPlug(1)->isActive());
  }

  BOOST_AUTO_TEST_CASE(test_command_activate_redo) {
    CommandActivate *command = new CommandActivate(robot, component->getMyPlug(1)->getShape());
    command->execute();
    command->undo();
    command->execute();
    BOOST_CHECK(!component->getMyPlug(0)->isActive());
    BOOST_CHECK(component->getMyPlug(1)->isActive());
  }

  BOOST_AUTO_TEST_CASE(test_command_activate_undo_previous_plug_not_active) {
    CommandActivate *command = new CommandActivate(robot, component->getMyPlug(1)->getShape());
    command->execute();
    command->undo();
    // currently if non was active before we just do not touch anything
    // TODO: Extend robot to be able to deactivate a given plug constistent
    BOOST_CHECK(component->getMyPlug(0)->isActive());
    BOOST_CHECK(!component->getMyPlug(1)->isActive());
  }

BOOST_AUTO_TEST_SUITE_END()


//----------------------------------------------------------------------------
class PreviousNotActivateFixture {
  public:
    PreviousNotActivateFixture() {
      polycodeMock = new PolycodeMock();
      robot = new Robot(polycodeMock);
      component = new ComponentMock();
      robot->setRoot(component);
    }

    PolycodeMock *polycodeMock;
    Robot *robot;
    ComponentMock *component;
};

BOOST_FIXTURE_TEST_SUITE(PreviousNotActivate, PreviousNotActivateFixture)

  BOOST_AUTO_TEST_CASE(test_command_activate_and_undo) {
    CommandActivate *command = new CommandActivate(robot, component->getMyPlug(1)->getShape());
    command->execute();
    command->undo();
    BOOST_CHECK(!component->getMyPlug(0)->isActive());
    BOOST_CHECK(!component->getMyPlug(1)->isActive());
  }

BOOST_AUTO_TEST_SUITE_END()



//----------------------------------------------------------------------------
class PlaceFixture {
  public:
    PlaceFixture() {
      deleted = false;
      polycodeMock = new PolycodeMock();
      robot = new Robot(polycodeMock);
      component1 = new ComponentMock();
      robot->setRoot(component1);
      robot->activate(component1->getMyPlug(0)->getShape());
      component2 = new ComponentMock(&deleted);
    }

    bool deleted;
    PolycodeMock *polycodeMock;
    Robot *robot;
    ComponentMock *component1;
    ComponentMock *component2;
};

BOOST_FIXTURE_TEST_SUITE(Place, PlaceFixture)

  BOOST_AUTO_TEST_CASE(test_command_place_execute_true_on_success) {
    CommandPlace *command = new CommandPlace(robot, component2);
    BOOST_CHECK(command->execute());
  }

  BOOST_AUTO_TEST_CASE(test_command_place_execute_false_on_failure) {
    robot->deactivate(component1->getMyPlug(0)->getShape());
    CommandPlace *command = new CommandPlace(robot, component2);
    BOOST_CHECK(!command->execute());
  }

  BOOST_AUTO_TEST_CASE(test_command_place_execute) {
    CommandPlace *command = new CommandPlace(robot, component2);
    command->execute();
    BOOST_CHECK(robot->getInPlace() == component2);
  }

  BOOST_AUTO_TEST_CASE(test_command_place_execute_command_destroy) {
    CommandPlace *command = new CommandPlace(robot, component2);
    command->execute();
    delete command;
    BOOST_CHECK(!deleted);
  }

  BOOST_AUTO_TEST_CASE(test_command_place_execute_restore_active_plug) {
    CommandPlace *command = new CommandPlace(robot, component2);
    command->execute();
    BOOST_CHECK(component2->getPart(0)->getPlug(0)->isActive());
  }

  BOOST_AUTO_TEST_CASE(test_command_place_undo) {
    CommandPlace *command = new CommandPlace(robot, component2);
    command->execute();
    command->undo();
    BOOST_CHECK(robot->getInPlace() == NULL);
  }

  BOOST_AUTO_TEST_CASE(test_command_place_undo_command_destroy) {
    CommandPlace *command = new CommandPlace(robot, component2);
    command->execute();
    command->undo();
    delete command;
    BOOST_CHECK(deleted);
  }

  BOOST_AUTO_TEST_CASE(test_command_place_undo_restore_active_plug) {
    CommandPlace *command = new CommandPlace(robot, component2);
    command->execute();
    command->undo();
    BOOST_CHECK(component1->getPart(0)->getPlug(0)->isActive());
  }

  BOOST_AUTO_TEST_CASE(test_command_place_redo) {
    CommandPlace *command = new CommandPlace(robot, component2);
    command->execute();
    command->undo();
    command->execute();
    BOOST_CHECK(robot->getInPlace() != NULL);
  }

BOOST_AUTO_TEST_SUITE_END()


//----------------------------------------------------------------------------
class RotateInPlaceFixture {
  public:
    RotateInPlaceFixture() {
      polycodeMock = new PolycodeMock();
      robot = new Robot(polycodeMock);
      component1 = new ComponentMock();
      robot->setRoot(component1);
      robot->activate(component1->getMyPlug(0)->getShape());
      component2 = new ComponentMock();
      robot->place(component2);
    }

    PolycodeMock *polycodeMock;
    Robot *robot;
    ComponentMock *component1;
    ComponentMock *component2;
};

BOOST_FIXTURE_TEST_SUITE(RotateInPlace, RotateInPlaceFixture)

  BOOST_AUTO_TEST_CASE(test_command_rotate_in_place_execute_true_on_success) {
    CommandRotateInPlace *command = new CommandRotateInPlace(robot, 1);
    BOOST_CHECK(command->execute());
  }

  BOOST_AUTO_TEST_CASE(test_command_rotate_in_place_execute_false_on_failure) {
    robot->remove(); // remove inplace
    CommandRotateInPlace *command = new CommandRotateInPlace(robot, 1);
    BOOST_CHECK(!command->execute());
  }

  BOOST_AUTO_TEST_CASE(test_command_rotate_in_place_execute) {
    CommandRotateInPlace *command = new CommandRotateInPlace(robot, 1);
    command->execute();
    // TODO: Check why the getShape()->getRotationEuler() do not reflect the action which obviously takes place
  }

  BOOST_AUTO_TEST_CASE(test_command_rotate_in_place_undo) {
    CommandRotateInPlace *command = new CommandRotateInPlace(robot, 1);
    command->execute();
    command->undo();
    // TODO: Check why the getShape()->getRotationEuler() do not reflect the action which obviously takes place
  }

  BOOST_AUTO_TEST_CASE(test_command_rotate_in_place_redo) {
    CommandRotateInPlace *command = new CommandRotateInPlace(robot, 1);
    command->execute();
    command->undo();
    command->execute();
    // TODO: Check why the getShape()->getRotationEuler() do not reflect the action which obviously takes place
  }

BOOST_AUTO_TEST_SUITE_END()


//----------------------------------------------------------------------------
class AddFixture {
  public:
    AddFixture() {
      deleted = false;
      polycodeMock = new PolycodeMock();
      robot = new Robot(polycodeMock);
      component1 = new ComponentMock();
      robot->setRoot(component1);
      robot->activate(component1->getMyPlug(0)->getShape());
      component2 = new ComponentMock(&deleted);
      robot->place(component2);
    }

    bool deleted;
    PolycodeMock *polycodeMock;
    Robot *robot;
    ComponentMock *component1;
    ComponentMock *component2;
};

BOOST_FIXTURE_TEST_SUITE(Add, AddFixture)

  BOOST_AUTO_TEST_CASE(test_command_add_execute_always_true) {
    CommandAdd *command = new CommandAdd(robot, component2);
    BOOST_CHECK(command->execute());
  }

  BOOST_AUTO_TEST_CASE(test_command_add_execute) {
    CommandAdd *command = new CommandAdd(robot, component2);
    command->execute();
    BOOST_CHECK(component1->get(0) == component2);
  }

  BOOST_AUTO_TEST_CASE(test_command_add_execute_command_destroy) {
    CommandAdd *command = new CommandAdd(robot, component2);
    command->execute();
    delete command;
    BOOST_CHECK(!deleted);
  }

  BOOST_AUTO_TEST_CASE(test_command_add_undo) {
    CommandAdd *command = new CommandAdd(robot, component2);
    command->execute();
    command->undo();
    BOOST_CHECK_THROW(component1->get(0), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(test_command_add_undo_command_destroy) {
    CommandAdd *command = new CommandAdd(robot, component2);
    command->execute();
    command->undo();
    delete command;
    BOOST_CHECK(!deleted);
  }

  BOOST_AUTO_TEST_CASE(test_command_add_undo_in_place_again) {
    CommandAdd *command = new CommandAdd(robot, component2);
    command->execute();
    command->undo();
    BOOST_CHECK(robot->getInPlace() != NULL);
  }

  BOOST_AUTO_TEST_CASE(test_command_add_undo_restore_selected_plug) {
    CommandAdd *command = new CommandAdd(robot, component2);
    command->execute();
    command->undo();
    BOOST_CHECK(robot->getActivePlug() == component1->getMyPlug(0));
  }

  BOOST_AUTO_TEST_CASE(test_command_add_redo) {
    CommandAdd *command = new CommandAdd(robot, component2);
    command->execute();
    command->undo();
    command->execute();
    BOOST_CHECK(component1->get(0));
  }

BOOST_AUTO_TEST_SUITE_END()


//----------------------------------------------------------------------------
class RemoveInPlaceFixture {
  public:
    RemoveInPlaceFixture() {
      polycodeMock = new PolycodeMock();
      robot = new Robot(polycodeMock);
      component1 = new ComponentMock();
      robot->setRoot(component1);
      robot->activate(component1->getMyPlug(0)->getShape());
      deleted = false;
      component2 = new ComponentMock(&deleted);
      robot->place(component2);
    }

    bool deleted;
    PolycodeMock *polycodeMock;
    Robot *robot;
    ComponentMock *component1;
    ComponentMock *component2;
};

BOOST_FIXTURE_TEST_SUITE(RemoveInPlace, RemoveInPlaceFixture)

  BOOST_AUTO_TEST_CASE(test_command_remove_in_place_execute_always_true) {
    CommandRemove *command = new CommandRemove(robot);
    BOOST_CHECK(command->execute());
  }

  BOOST_AUTO_TEST_CASE(test_command_remove_in_place_execute) {
    CommandRemove *command = new CommandRemove(robot);
    command->execute();
    BOOST_CHECK(robot->getInPlace() == NULL);
  }

  BOOST_AUTO_TEST_CASE(test_command_remove_in_place_execute_command_presist_dont_destroy_component) {
    CommandRemove *command = new CommandRemove(robot);
    command->execute();
    BOOST_CHECK(!deleted);
  }

  BOOST_AUTO_TEST_CASE(test_command_remove_in_place_execute_command_destroy) {
    CommandRemove *command = new CommandRemove(robot);
    command->execute();
    delete command;
    BOOST_CHECK(deleted);
  }

  BOOST_AUTO_TEST_CASE(test_command_remove_in_place_undo) {
    CommandRemove *command = new CommandRemove(robot);
    command->execute();
    command->undo();
    BOOST_CHECK(robot->getInPlace() == component2);
  }

  BOOST_AUTO_TEST_CASE(test_command_remove_in_place_undo_destruct) {
    CommandRemove *command = new CommandRemove(robot);
    command->execute();
    command->undo();
    delete command;
    BOOST_CHECK(!deleted);
  }

  BOOST_AUTO_TEST_CASE(test_command_remove_in_place_redo) {
    CommandRemove *command = new CommandRemove(robot);
    command->execute();
    command->undo();
    command->execute();
    BOOST_CHECK(robot->getInPlace() == NULL);
  }
BOOST_AUTO_TEST_SUITE_END()


//----------------------------------------------------------------------------
class RemoveAddedFixture {
  public:
    RemoveAddedFixture() {
      polycodeMock = new PolycodeMock();
      robot = new Robot(polycodeMock);
      component1 = new ComponentMock();
      robot->setRoot(component1);
      robot->activate(component1->getMyPlug(0)->getShape());
      deleted = false;
      component2 = new ComponentMock(&deleted);
      robot->place(component2);
      robot->add();
      robot->activate(component2->getMyPlug(1)->getShape());
    }

    bool deleted;
    PolycodeMock *polycodeMock;
    Robot *robot;
    ComponentMock *component1;
    ComponentMock *component2;
};

BOOST_FIXTURE_TEST_SUITE(RemoveAdded, RemoveAddedFixture)

  BOOST_AUTO_TEST_CASE(test_command_remove_added_execute_true_on_success) {
    CommandRemove *command = new CommandRemove(robot);
    BOOST_CHECK(command->execute());
  }

  BOOST_AUTO_TEST_CASE(test_command_remove_added_execute_false_on_failure) {
    robot->deactivate(component2->getMyPlug(1)->getShape());
    CommandRemove *command = new CommandRemove(robot);
    BOOST_CHECK(!command->execute());
  }

  BOOST_AUTO_TEST_CASE(test_command_remove_added_execute) {
    CommandRemove *command = new CommandRemove(robot);
    command->execute();
    BOOST_CHECK(robot->getInPlace() == component2);
  }

  BOOST_AUTO_TEST_CASE(test_command_remove_added_execute_command_destroy) {
    CommandRemove *command = new CommandRemove(robot);
    command->execute();
    delete command;
    BOOST_CHECK(!deleted);
  }

  BOOST_AUTO_TEST_CASE(test_command_remove_added_undo) {
    CommandRemove *command = new CommandRemove(robot);
    command->execute();
    command->undo();
    BOOST_CHECK(component1->get(0) == component2);
  }

  BOOST_AUTO_TEST_CASE(test_command_remove_added_undo_not_in_place) {
    CommandRemove *command = new CommandRemove(robot);
    command->execute();
    command->undo();
    BOOST_CHECK(robot->getInPlace() == NULL);
  }

  BOOST_AUTO_TEST_CASE(test_command_remove_added_undo_restore_active_plug) {
    CommandRemove *command = new CommandRemove(robot);
    command->execute();
    command->undo();
    BOOST_CHECK(robot->getActivePlug() == component2->getMyPlug(1));
  }

  BOOST_AUTO_TEST_CASE(test_command_remove_added_undo_command_destroy) {
    CommandRemove *command = new CommandRemove(robot);
    command->execute();
    command->undo();
    delete command;
    BOOST_CHECK(!deleted);
  }

  BOOST_AUTO_TEST_CASE(test_command_remove_added_redo) {
    CommandRemove *command = new CommandRemove(robot);
    command->execute();
    command->undo();
    command->execute();
    BOOST_CHECK(robot->getInPlace() == component2);
  }

BOOST_AUTO_TEST_SUITE_END()


//----------------------------------------------------------------------------
class RemoveSetRootFixture {
  public:
    RemoveSetRootFixture() {
      polycodeMock = new PolycodeMock();
      robot = new Robot(polycodeMock);
      component = new ComponentMock();
      robot->setRoot(component);
      robot->activate(component->getMyPlug(0)->getShape());
    }

    PolycodeMock *polycodeMock;
    Robot *robot;
    ComponentMock *component;
};

BOOST_FIXTURE_TEST_SUITE(RemoveSetRoot, RemoveSetRootFixture)

  BOOST_AUTO_TEST_CASE(test_command_remove_set_root_execute) {
    CommandRemove *command = new CommandRemove(robot);
    command->execute();
    BOOST_CHECK(robot->isEmpty());
  }

  BOOST_AUTO_TEST_CASE(test_command_remove_set_root_undo) {
    CommandRemove *command = new CommandRemove(robot);
    command->execute();
    command->undo();
    BOOST_CHECK(!robot->isEmpty());
  }

  BOOST_AUTO_TEST_CASE(test_command_remove_set_root_undo_redo) {
    CommandRemove *command = new CommandRemove(robot);
    command->execute();
    command->undo();
    command->execute();
    BOOST_CHECK(robot->isEmpty());
  }

BOOST_AUTO_TEST_SUITE_END()


//----------------------------------------------------------------------------
class RemoveNotActivateFixture {
  public:
    RemoveNotActivateFixture() {
      polycodeMock = new PolycodeMock();
      robot = new Robot(polycodeMock);
      component = new ComponentMock();
      robot->setRoot(component);
    }

    PolycodeMock *polycodeMock;
    Robot *robot;
    ComponentMock *component;
};

BOOST_FIXTURE_TEST_SUITE(RemoveNotActivate, RemoveNotActivateFixture)

  BOOST_AUTO_TEST_CASE(test_command_remove_set_root_execute) {
    CommandRemove *command = new CommandRemove(robot);
    command->execute();
    BOOST_CHECK(!robot->isEmpty());
  }

  BOOST_AUTO_TEST_CASE(test_command_remove_set_root_undo) {
    CommandRemove *command = new CommandRemove(robot);
    command->execute();
    command->undo();
    BOOST_CHECK(!robot->isEmpty());
  }

  BOOST_AUTO_TEST_CASE(test_command_remove_set_root_undo_redo) {
    CommandRemove *command = new CommandRemove(robot);
    command->execute();
    command->undo();
    command->execute();
    BOOST_CHECK(!robot->isEmpty());
  }

BOOST_AUTO_TEST_SUITE_END()

