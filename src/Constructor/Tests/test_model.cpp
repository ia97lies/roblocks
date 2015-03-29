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

class KnobMock : public Knob {
  public:
    KnobMock() {
      m_shape = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 1, 1);
    }
    ~KnobMock() {}
    Polycode::Entity *getShape() { return m_shape; }
    void activate(bool on) { }
    void handleInput(Polycode::Vector3 delta) { }
  private:
    Polycode::Entity *m_shape;
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


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
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
class RootActivateFixture {
  public:
    RootActivateFixture() {
      component = new ComponentMock();
      model.setRoot(component);
    }
    Model model;
    ComponentMock *component;
};

BOOST_FIXTURE_TEST_SUITE(RootActivateOne, RootActivateFixture)

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
class TwoElementActivateFixture {
  public:
    TwoElementActivateFixture() {
      component[0] = new ComponentMock();
      model.setRoot(component[0]);
      component[1] = new ComponentMock();
      component[0]->add(component[1]);
      component[2] = new ComponentMock();
    }
    Model model;
    ComponentMock *component[3];
};

BOOST_FIXTURE_TEST_SUITE(RootActivateTwo, TwoElementActivateFixture)

  BOOST_AUTO_TEST_CASE(test_model_two_element_activate_null) {
    model.activate(NULL);
    BOOST_CHECK(model.getActiveComponent() == NULL);
  }

  BOOST_AUTO_TEST_CASE(test_model_two_element_activate_root) {
    model.activate(component[0]->getMyPlug(0)->getShape());
    BOOST_CHECK(model.getActiveComponent() == component[0]);
  }

  BOOST_AUTO_TEST_CASE(test_model_two_element_activate_second_get_component) {
    model.activate(component[1]->getMyPlug(0)->getShape());
    BOOST_CHECK(model.getActiveComponent() == component[1]);
  }

  BOOST_AUTO_TEST_CASE(test_model_two_element_activate_second_get_part) {
    model.activate(component[1]->getMyPlug(0)->getShape());
    BOOST_CHECK(model.getActivePart() == component[1]->getPart(0));
  }

  BOOST_AUTO_TEST_CASE(test_model_two_element_activate_second_get_plug) {
    model.activate(component[1]->getMyPlug(0)->getShape());
    BOOST_CHECK(model.getActivePlug() == component[1]->getMyPlug(0));
  }

  BOOST_AUTO_TEST_CASE(test_model_two_element_activate_exist_activate_non_exist) {
    model.activate(component[1]->getMyPlug(0)->getShape());
    model.activate(component[2]->getMyPlug(0)->getShape());
    BOOST_CHECK(model.getActiveComponent() == NULL);
  }

BOOST_AUTO_TEST_SUITE_END()


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
class OneKnobOnRootActivateFixture {
  public:
    OneKnobOnRootActivateFixture() {
      component = new ComponentMock();
      model.setRoot(component);
      knob = new KnobMock();
      component->getPart(0)->setKnob(knob);
    }
    Model model;
    ComponentMock *component;
    KnobMock *knob;
};

BOOST_FIXTURE_TEST_SUITE(OneKnobOnRootActivate, OneKnobOnRootActivateFixture)

  BOOST_AUTO_TEST_CASE(test_model_root_one_knob_null) {
    model.activate(NULL);
    BOOST_CHECK(model.getActiveKnob() == NULL);
  }

  BOOST_AUTO_TEST_CASE(test_model_root_one_knob_activate_knob) {
    model.activate(component->getPart(0)->getKnob()->getShape());
    BOOST_CHECK(model.getActiveKnob() == component->getPart(0)->getKnob());
  }

BOOST_AUTO_TEST_SUITE_END()


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
class KnobActivateFixture {
  public:
    KnobActivateFixture() {
      component[0] = new ComponentMock();
      component[1] = new ComponentMock();
      component[2] = new ComponentMock();
      model.setRoot(component[0]);
      knob[0] = new KnobMock();
      component[0]->getPart(0)->setKnob(knob[0]);
      knob[1] = new KnobMock();
      component[1]->getPart(0)->setKnob(knob[1]);
      knob[2] = new KnobMock();
      component[2]->getPart(0)->setKnob(knob[2]);
      component[0]->add(component[1]);
    }
    Model model;
    ComponentMock *component[3];
    KnobMock *knob[3];
};

BOOST_FIXTURE_TEST_SUITE(KnobOnRootActivate, KnobActivateFixture)

  BOOST_AUTO_TEST_CASE(test_model_knob_null) {
    model.activate(NULL);
    BOOST_CHECK(model.getActiveKnob() == NULL);
  }

  BOOST_AUTO_TEST_CASE(test_model_knob_activate_knob) {
    model.activate(component[1]->getPart(0)->getKnob()->getShape());
    BOOST_CHECK(model.getActiveKnob() == component[1]->getPart(0)->getKnob());
  }

  BOOST_AUTO_TEST_CASE(test_model_knob_activate_non_existing_knob) {
    model.activate(component[2]->getPart(0)->getKnob()->getShape());
    BOOST_CHECK(model.getActiveKnob() == NULL);
  }

  BOOST_AUTO_TEST_CASE(test_model_knob_activate_wrong_shape) {
    model.activate(component[2]->getPart(0)->getShape());
    BOOST_CHECK(model.getActiveKnob() == NULL);
  }

BOOST_AUTO_TEST_SUITE_END()











