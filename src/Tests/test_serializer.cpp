//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestSerializer
#include <boost/test/unit_test.hpp>
#include "Polycode.h"
#include "Writer.hpp"
#include "Serializer.hpp"
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

    virtual std::string getName() {
      return "Test.Mock";
    }

    virtual int getNoParts() { return 2; }
    virtual Part *getPart(int i) { return m_part[i]; }
    virtual void enable(bool on) {};
    Plug *getMyPlug(int i) { return m_plug[i]; }

  private:
    Part *m_part[2];
    Plug *m_plug[4];
};

class WriterMock : public Writer {
  public:
    WriterMock() {}
    virtual ~WriterMock() {};
    virtual void write(Compound *compound) { 
      Component *component = dynamic_cast<Component *>(compound);
      if (component) {
        result += component->getName(); 
      }
    }

    std::string result;
};

BOOST_AUTO_TEST_CASE(test_serializer_instantiate) {
  Serializer serializer(NULL, NULL);
}

BOOST_AUTO_TEST_CASE(test_serializer_serialize_NULL_writer) {
  ComponentMock comp;
  Serializer serializer(&comp, NULL);
}

BOOST_AUTO_TEST_CASE(test_serializer_serialize_one_element) {
  ComponentMock comp;
  WriterMock writer;
  Serializer serializer(&comp, &writer);
  BOOST_CHECK(writer.result == "Test.Mock");
}

