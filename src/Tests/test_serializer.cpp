//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestSerializer
#include <boost/test/unit_test.hpp>
#include "Polycode.h"
#include "Printer.hpp"
#include "Serializer.hpp"
#include "Component.hpp"

using namespace Synthetics;
using namespace Polycode;

class ComponentMock : public Component {
  public:
    ComponentMock(std::string name) { m_name = name; }
    virtual ~ComponentMock() {}

    virtual std::string getName() {
      return m_name;
    }
    virtual int getNoParts() { return 0; }
    virtual Part *getPart(int i) { return NULL; }
    virtual void enable(bool on) {};
    Plug *getMyPlug(int i) { return NULL; }
  private:
    std::string m_name;
};

class PrinterMock : public Printer {
  public:
    PrinterMock() { result = ":"; }
    virtual ~PrinterMock() {};
    virtual void write(Compound *parent, Compound *compound) { 
      Component *component = dynamic_cast<Component *>(compound);
      Component *mother = dynamic_cast<Component *>(parent);
      if (component) {
        Tag *tag = component->getTag();
        result += (mother ? mother->getName() + "->" : "") + (!tag ? "<create>" : "") + component->getName() + ":"; 
        if (!tag) {
          component->setTag(new Tag());
        }
      }
    }

    std::string result;
};

BOOST_AUTO_TEST_CASE(test_serializer_instantiate) {
  Serializer serializer(NULL, NULL);
}

BOOST_AUTO_TEST_CASE(test_serializer_serialize_NULL_printer) {
  ComponentMock comp("Foo");
  Serializer serializer(&comp, NULL);
}

BOOST_AUTO_TEST_CASE(test_serializer_serialize_one_element) {
  ComponentMock comp("Test.Mock");
  PrinterMock printer;
  Serializer serializer(&comp, &printer);
  BOOST_CHECK(printer.result == ":<create>Test.Mock:");
}

BOOST_AUTO_TEST_CASE(test_serializer_serialize_more_element) {
  ComponentMock mother("Test.Mother");
  ComponentMock comp1("Test.1_1");
  ComponentMock comp2("Test.1_2");
  mother.add(&comp1);
  mother.add(&comp2);
  ComponentMock comp3("Test.2_1");
  ComponentMock comp4("Test.2_2");
  comp1.add(&comp3);
  comp2.add(&comp3);
  comp2.add(&comp4);
  PrinterMock printer;
  Serializer serializer(&mother, &printer);
  fprintf(stderr, "RESULT: %s\n", printer.result.c_str());
  BOOST_CHECK(printer.result == ":<create>Test.Mother:Test.Mother-><create>Test.1_1:Test.1_1-><create>Test.2_1:Test.Mother-><create>Test.1_2:Test.1_2->Test.2_1:Test.1_2-><create>Test.2_2:");
}

