//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestComponentPrinter
#include <boost/test/unit_test.hpp>
#include "Polycode.h"
#include "Printer.hpp"
#include "Serializer.hpp"
#include "Component.hpp"
#include "ComponentPrinter.hpp"

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

class WriterMock : public Writer {
    public:
      WriterMock() {};
      virtual ~WriterMock() {};
      virtual void writeln(std::string line) {
      }
};

BOOST_AUTO_TEST_CASE(test_component_printer_instantiate) {
  ComponentPrinter save = ComponentPrinter(NULL);
}

BOOST_AUTO_TEST_CASE(test_component_printer_only_mother) {
  ComponentMock mock("Root.Object");
  WriterMock writer;
  ComponentPrinter save(&writer);
  Serializer serializer(&mock, &save);
}
