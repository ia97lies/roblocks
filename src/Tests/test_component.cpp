//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestComponent
#include <boost/test/unit_test.hpp>
#include "Polycode.h"
#include "Component.hpp"

using namespace Synthetics;
using namespace Polycode;

class PartMock : public Part {
  public:
    PartMock() {
      m_shape = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 1, 1);
    }
    ~PartMock() {}
    Polycode::Entity *getShape() { return m_shape; }
    float getMass() { return 1; }
  private:
    Polycode::Entity *m_shape;
};

class ComponentMock : public Component {
  public:
    ComponentMock() { 
      m_part[0] = new PartMock();
      m_plug[0] = new Plug(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_part[0]->addPlug(m_plug[0]);
      m_plug[3] = new Plug(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_part[0]->addPlug(m_plug[3]);

      m_part[1] = new PartMock();
      m_plug[1] = new Plug(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_part[1]->addPlug(m_plug[1]);
      m_plug[2] = new Plug(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_part[1]->addPlug(m_plug[2]);

    }
    virtual ~ComponentMock() {}

    virtual int getNoParts() { return 2; }
    virtual Part *getPart(int i) { return m_part[i]; }
    virtual void enable(bool on) {}
    virtual void update(Plug *sendingPlug, Polycode::Vector3 delta) {}
    Plug *getMyPlug(int i) { return m_plug[i]; }
  private:
    Part *m_part[2];
    Plug *m_plug[4];
};

BOOST_AUTO_TEST_CASE(test_component_instantiate) {
  ComponentMock *mock = new ComponentMock();
  delete mock;
}

BOOST_AUTO_TEST_CASE(test_component_part_by_plug_shape) {
  ComponentMock *mock = new ComponentMock();
  BOOST_CHECK(mock->getPartByPlug(mock->getMyPlug(0)->getShape()) == mock->getPart(0));
  BOOST_CHECK(mock->getPartByPlug(mock->getMyPlug(1)->getShape()) == mock->getPart(1));
  BOOST_CHECK(mock->getPartByPlug(mock->getMyPlug(2)->getShape()) == mock->getPart(1));
  BOOST_CHECK(mock->getPartByPlug(mock->getMyPlug(3)->getShape()) == mock->getPart(0));
  delete mock;
}

class SimpleSensorMock : public Component {
  public:
    SimpleSensorMock() { 
      m_part = new PartMock();
      m_plug = new Plug(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_plug->setInput(false);
      m_part->addPlug(m_plug);
    }
    virtual ~SimpleSensorMock() {}

    void setValue(Vector3 value) {
      m_value = value;
    }

    virtual int getNoParts() { return 1; }
    virtual Part *getPart(int i) { return m_part; }
    virtual void enable(bool on) {}
    virtual void update(Plug *sendingPlug, Polycode::Vector3 delta) {}
    Plug *getMyPlug(int i) { return m_plug; }

    void updateNg() {
      m_plug->setValue(m_value);
      m_plug->getConnectedPlug()->setValue(m_value);
    }

  private:
    Part *m_part;
    Plug *m_plug;
    Vector3 m_value;
};

class SimpleActorMock : public Component {
  public:
    SimpleActorMock() { 
      m_part = new PartMock();
      m_plug = new Plug(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_plug->setInput(true);
      m_part->addPlug(m_plug);
    }
    virtual ~SimpleActorMock() {}

    virtual int getNoParts() { return 1; }
    virtual Part *getPart(int i) { return m_part; }
    virtual void enable(bool on) {}
    virtual void update(Plug *sendingPlug, Polycode::Vector3 delta) {}
    Plug *getMyPlug(int i) { return m_plug; }

  private:
    Part *m_part;
    Plug *m_plug;
};

class SimpleHubMock : public Component {
  public:
    SimpleHubMock() { 
      m_part = new PartMock();
      m_plug[0] = new Plug(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_plug[0]->setInOut(true);
      m_part->addPlug(m_plug[0]);
      m_plug[1] = new Plug(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_plug[1]->setInOut(true);
      m_part->addPlug(m_plug[1]);
      m_plug[2] = new Plug(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_plug[2]->setInOut(true);
      m_part->addPlug(m_plug[2]);
    }
    virtual ~SimpleHubMock() {}

    Vector3 getValue(int i) {
      return m_plug[i]->getValue();
    }

    virtual int getNoParts() { return 1; }
    virtual Part *getPart(int i) { return m_part; }
    virtual void enable(bool on) {}
    virtual void update(Plug *sendingPlug, Polycode::Vector3 delta) {}
    Plug *getMyPlug(int i) { return m_plug[i]; }

  private:
    Part *m_part;
    Plug *m_plug[3];
};

BOOST_AUTO_TEST_CASE(test_component_sensor_signals_actor) {
  SimpleSensorMock *sensor = new SimpleSensorMock();
  SimpleActorMock *actor = new SimpleActorMock();

  sensor->add(actor);
  sensor->getPart(0)->getPlug(0)->setConnectedPlug(actor->getPart(0)->getPlug(0));
  actor->getPart(0)->getPlug(0)->setConnectedPlug(sensor->getPart(0)->getPlug(0));

  sensor->setValue(Vector3(20,0,0));

  BOOST_CHECK(actor->getOutput() == Vector3(0,0,0));

  sensor->updateNg();
  actor->updateNg();

  BOOST_CHECK(actor->getOutput() == Vector3(20,0,0));
}

BOOST_AUTO_TEST_CASE(test_component_sensor_signals_actor_via_hub) {
  SimpleSensorMock *sensor = new SimpleSensorMock();
  SimpleHubMock *hub = new SimpleHubMock();
  SimpleActorMock *actor = new SimpleActorMock();

  sensor->add(hub);
  sensor->getPart(0)->getPlug(0)->setConnectedPlug(hub->getPart(0)->getPlug(0));
  hub->getPart(0)->getPlug(0)->setConnectedPlug(sensor->getPart(0)->getPlug(0));
  hub->add(actor);
  hub->getPart(0)->getPlug(1)->setConnectedPlug(actor->getPart(0)->getPlug(0));
  actor->getPart(0)->getPlug(0)->setConnectedPlug(hub->getPart(0)->getPlug(1));

  sensor->setValue(Vector3(20,0,0));

  BOOST_CHECK(actor->getOutput() == Vector3(0,0,0));

  sensor->updateNg();
  hub->updateNg();
  actor->updateNg();

  BOOST_CHECK(hub->getValue(0) == Vector3(20,0,0));
  BOOST_CHECK(hub->getValue(1) == Vector3(20,0,0));

  sensor->updateNg();
  hub->updateNg();
  actor->updateNg();

  BOOST_CHECK(hub->getValue(1) == Vector3(20,0,0));
  BOOST_CHECK(actor->getOutput() == Vector3(20,0,0));
}

BOOST_AUTO_TEST_CASE(test_component_two_sensor_signals_actor_via_hub) {
  SimpleSensorMock *sensor[2] = { new SimpleSensorMock(), new SimpleSensorMock() };
  SimpleHubMock *hub = new SimpleHubMock();
  SimpleActorMock *actor = new SimpleActorMock();

  sensor[0]->add(hub);
  sensor[0]->getPart(0)->getPlug(0)->setConnectedPlug(hub->getPart(0)->getPlug(0));
  hub->getPart(0)->getPlug(0)->setConnectedPlug(sensor[0]->getPart(0)->getPlug(0));
  hub->add(actor);
  hub->getPart(0)->getPlug(1)->setConnectedPlug(actor->getPart(0)->getPlug(0));
  actor->getPart(0)->getPlug(0)->setConnectedPlug(hub->getPart(0)->getPlug(1));
  sensor[1]->add(hub);
  sensor[1]->getPart(0)->getPlug(0)->setConnectedPlug(hub->getPart(0)->getPlug(2));
  hub->getPart(0)->getPlug(2)->setConnectedPlug(sensor[1]->getPart(0)->getPlug(0));

  sensor[0]->setValue(Vector3(20,0,0));
  sensor[1]->setValue(Vector3(13,0,0));

  BOOST_CHECK(actor->getOutput() == Vector3(0,0,0));

  sensor[0]->updateNg();
  sensor[1]->updateNg();
  hub->updateNg();
  actor->updateNg();

  BOOST_CHECK(hub->getValue(0) == Vector3(33,0,0));
  BOOST_CHECK(hub->getValue(1) == Vector3(33,0,0));
  BOOST_CHECK(hub->getValue(2) == Vector3(33,0,0));
  BOOST_CHECK(actor->getOutput() == Vector3(33,0,0));

  sensor[0]->updateNg();
  sensor[1]->updateNg();
  hub->updateNg();
  actor->updateNg();

  BOOST_CHECK(hub->getValue(1) == Vector3(33,0,0));
  BOOST_CHECK(actor->getOutput() == Vector3(33,0,0));
}

BOOST_AUTO_TEST_CASE(test_component_two_sensor_signals_actor_via_two_hub) {
  SimpleSensorMock *sensor[2] = { new SimpleSensorMock(), new SimpleSensorMock() };
  SimpleHubMock *hub[2] = { new SimpleHubMock(), new SimpleHubMock() };
  SimpleActorMock *actor = new SimpleActorMock();

  sensor[0]->add(hub[0]);
  sensor[0]->getPart(0)->getPlug(0)->setConnectedPlug(hub[0]->getPart(0)->getPlug(0));
  hub[0]->getPart(0)->getPlug(0)->setConnectedPlug(sensor[0]->getPart(0)->getPlug(0));

  hub[0]->add(actor);
  hub[0]->getPart(0)->getPlug(1)->setConnectedPlug(actor->getPart(0)->getPlug(0));
  actor->getPart(0)->getPlug(0)->setConnectedPlug(hub[0]->getPart(0)->getPlug(1));

  hub[0]->add(hub[1]);
  hub[0]->getPart(0)->getPlug(2)->setConnectedPlug(hub[1]->getPart(0)->getPlug(0));
  hub[1]->getPart(0)->getPlug(0)->setConnectedPlug(hub[0]->getPart(0)->getPlug(2));

  sensor[1]->add(hub[1]);
  sensor[1]->getPart(0)->getPlug(0)->setConnectedPlug(hub[1]->getPart(0)->getPlug(1));
  hub[1]->getPart(0)->getPlug(1)->setConnectedPlug(sensor[1]->getPart(0)->getPlug(0));

  sensor[0]->setValue(Vector3(20,0,0));
  sensor[1]->setValue(Vector3(13,0,0));

  BOOST_CHECK(actor->getOutput() == Vector3(0,0,0));

  sensor[0]->updateNg();
  sensor[1]->updateNg();
  hub[0]->updateNg();
  hub[1]->updateNg();
  actor->updateNg();

  BOOST_CHECK(hub[0]->getValue(0) == Vector3(20,0,0));
  BOOST_CHECK(hub[0]->getValue(1) == Vector3(20,0,0));
  BOOST_CHECK(hub[0]->getValue(2) == Vector3(20,0,0));
  BOOST_CHECK(hub[1]->getValue(0) == Vector3(13,0,0));
  BOOST_CHECK(hub[1]->getValue(1) == Vector3(33,0,0));
  BOOST_CHECK(actor->getOutput() == Vector3(20,0,0));

  // check that it will be stable
  for (int i = 0; i < 10; i++) {
    sensor[0]->updateNg();
    sensor[1]->updateNg();
    hub[0]->updateNg();
    hub[1]->updateNg();
    actor->updateNg();

    BOOST_CHECK(hub[0]->getValue(1) == Vector3(33,0,0));
    BOOST_CHECK(actor->getOutput() == Vector3(33,0,0));
  }
}

