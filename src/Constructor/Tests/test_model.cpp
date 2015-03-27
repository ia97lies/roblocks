//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestConstructorCommands
#include <boost/test/unit_test.hpp>
#include "PolycodeFacade.hpp"
#include "Plug.hpp"
#include "Components/Factory.hpp"
#include "Constructor/Model.hpp"

using namespace Synthetics;
using namespace Synthetics::Constructor;
using namespace Polycode;

class PolycodeMock : public PolycodeFacade {
  public:
    PolycodeMock() : PolycodeFacade(NULL, NULL) {}
    ~PolycodeMock() {}
 
    virtual void addEntity(Polycode::Entity *entity) { }
    virtual void trackCollisionEntity(Polycode::Entity *entity) { }
    virtual void removeEntity(Polycode::Entity *entity) { }
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

BOOST_AUTO_TEST_CASE(test_model_instantiate) {
  Model model();
}

BOOST_AUTO_TEST_CASE(test_model_set_get_root) {
  Model model;
  ComponentMock *component = new ComponentMock();
  model.setRoot(component);
  BOOST_CHECK(model.getRoot() == component);
}

BOOST_AUTO_TEST_CASE(test_model_get_root_default) {
  Model model;
  ComponentMock *component = new ComponentMock();
  BOOST_CHECK(model.getRoot() == NULL);
}

BOOST_AUTO_TEST_CASE(test_model_set_root_destroy) {
  bool deleted = false;
  {
    Model model;
    ComponentMock *component = new ComponentMock(&deleted);
    model.setRoot(component);
  }
  BOOST_CHECK(deleted);
}

BOOST_AUTO_TEST_CASE(test_model_empty_get_default_active_component) {
  Model model;
  BOOST_CHECK(model.getActiveComponent() == NULL);
}

BOOST_AUTO_TEST_CASE(test_model_empty_get_default_active_part) {
  Model model;
  BOOST_CHECK(model.getActivePart() == NULL);
}

BOOST_AUTO_TEST_CASE(test_model_empty_get_default_active_plug) {
  Model model;
  BOOST_CHECK(model.getActivePlug() == NULL);
}

BOOST_AUTO_TEST_CASE(test_model_empty_activate_null) {
  Model model;
  model.activate(NULL);
  BOOST_CHECK(model.getActiveComponent() == NULL);
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
class RootActivateOneFixture {
  public:
    RootActivateOneFixture() {
      component = new ComponentMock();
      model.setRoot(component);
      model.activate(NULL);
    }
    Model model;
    ComponentMock *component;
};

BOOST_FIXTURE_TEST_SUITE(RootActivateOne, RootActivateOneFixture)

  BOOST_AUTO_TEST_CASE(test_model_one_element_activate_null) {
    model.activate(NULL);
    BOOST_CHECK(model.getActiveComponent() == NULL);
  }

  BOOST_AUTO_TEST_CASE(test_model_one_element_activate_one) {
    model.activate(component->getMyPlug(0)->getShape());
    BOOST_CHECK(model.getActiveComponent() == component);
  }

  BOOST_AUTO_TEST_CASE(test_model_one_element_activate_one_get_active_part) {
    model.activate(component->getMyPlug(1)->getShape());
    BOOST_CHECK(model.getActivePart() == component->getPart(0));
  }

  BOOST_AUTO_TEST_CASE(test_model_one_element_activate_one_get_active_plug) {
    model.activate(component->getMyPlug(1)->getShape());
    BOOST_CHECK(model.getActivePlug() == component->getMyPlug(1));
  }

BOOST_AUTO_TEST_SUITE_END()

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
class RootActivateTwoFixture {
  public:
    RootActivateTwoFixture() {
      component[0] = new ComponentMock();
      component[1] = new ComponentMock();
      component[0]->add(component[1]);
      model.setRoot(component[0]);
      model.activate(NULL);
    }
    Model model;
    ComponentMock *component[2];
};

BOOST_FIXTURE_TEST_SUITE(RootActivateTwo, RootActivateTwoFixture)

  BOOST_AUTO_TEST_CASE(test_model_two_element_activate_null) {
    model.activate(NULL);
    BOOST_CHECK(model.getActiveComponent() == NULL);
  }

  BOOST_AUTO_TEST_CASE(test_model_two_element_activate_root) {
    model.activate(component[0]->getMyPlug(0)->getShape());
    BOOST_CHECK(model.getActiveComponent() == component[0]);
  }

  BOOST_AUTO_TEST_CASE(test_model_two_element_activate_second) {
    model.activate(component[1]->getMyPlug(0)->getShape());
    BOOST_CHECK(model.getActiveComponent() == component[1]);
  }

BOOST_AUTO_TEST_SUITE_END()

