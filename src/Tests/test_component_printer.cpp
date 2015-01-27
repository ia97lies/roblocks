//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestComponentPrinter
#include <boost/test/unit_test.hpp>
#include "Polycode.h"
#include "PolycodeFacade.hpp"
#include "Robot.hpp"
#include "Printer.hpp"
#include "Serializer.hpp"
#include "Component.hpp"
#include "ComponentPrinter.hpp"

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
    ComponentMock(std::string name) { 
      m_name = name; 
      m_part = new PartMock();
      m_plug[0] = new PlugMock(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_part->addPlug(m_plug[0]);
      m_plug[1] = new PlugMock(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_part->addPlug(m_plug[1]);
    }

    ~ComponentMock() {}

    std::string getName() {
      return m_name;
    }

    int getNoParts() { return 1; }
    Part *getPart(int i) { return m_part; }
    void enable(bool on) {}
    PlugMock *getMyPlug(int i) { return m_plug[i]; }

  private:
    std::string m_name;
    Part *m_part;
    PlugMock *m_plug[2];
};

class WriterMock : public Writer {
    public:
      WriterMock() { result = ""; }
      virtual ~WriterMock() {}
      virtual void writeln(std::string line) {
        result += line + "\n";
      }
      std::string result;
};

BOOST_AUTO_TEST_CASE(test_component_printer_instantiate) {
  ComponentPrinter save = ComponentPrinter(NULL);
}

BOOST_AUTO_TEST_CASE(test_component_printer_only_mother) {
  PolycodeMock polycodeMock;
  WriterMock writer;

  Robot *robot = new Robot(&polycodeMock);
  ComponentMock *componentMock = new ComponentMock("Root.Object");

  robot->add(componentMock);

  ComponentPrinter save(&writer);
  Serializer serializer(componentMock, &save);
  std::string ref = 
  "constructor = Require \"libConstructor\")\n"
  "factory = constructor:getFactory()\n"
  "mother = factory:create(\"Root.Object\")\n"
  "constructor:setMother(mother)\n"
  "current = mother\n";
  BOOST_CHECK(writer.result == ref);
}

BOOST_AUTO_TEST_CASE(test_component_printer_two_component) {
  WriterMock writer;
  PolycodeMock *polycodeMock = new PolycodeMock();
  Robot *robot = new Robot(polycodeMock);

  ComponentMock *root = new ComponentMock("Root.Object");
  robot->add(root);
  robot->activate(root->getMyPlug(0)->getShape());
  ComponentMock *componentMock = new ComponentMock("Object.1");
  robot->place(componentMock);
  robot->add();

  ComponentPrinter save(&writer);
  Serializer serializer(root, &save);
  fprintf(stderr, "\n%s\n", writer.result.c_str());

  BOOST_CHECK(false);
}

