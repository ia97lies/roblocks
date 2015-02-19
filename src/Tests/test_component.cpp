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

class SimpleSensorMock : public Component {
  public:
    SimpleSensorMock() { 
      m_part = new PartMock();
      m_plug = new Plug(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_plug->setInput(false);
      m_part->addPlug(m_plug);
    }
    virtual ~SimpleSensorMock() {}

    virtual int getNoParts() { return 1; }
    virtual Part *getPart(int i) { return m_part; }
    virtual void enable(bool on) {}
    virtual void update(Plug *sendingPlug, Polycode::Vector3 delta) {}
    Plug *getMyPlug(int i) { return m_plug; }
  private:
    Part *m_part;
    Plug *m_plug;
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

BOOST_AUTO_TEST_CASE(test_component_sensor_signals_actor) {
  SimpleSensorMock *sensor = new SimpleSensorMock();
  SimpleActorMock *actor = new SimpleActorMock();

  sensor->add(actor);
  sensor->getPart(0)->getPlug(0)->setConnectedPlug(actor->getPart(0)->getPlug(0));
  actor->getPart(0)->getPlug(0)->setConnectedPlug(sensor->getPart(0)->getPlug(0));


}

