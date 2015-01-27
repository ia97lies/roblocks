//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "ComponentPrinter.hpp"

namespace Synthetics {

  ComponentPrinter::ComponentPrinter(Writer *writer) {
    isMotherCreated = false;
    m_writer = writer;
  }

  ComponentPrinter::~ComponentPrinter() {
  }

  void ComponentPrinter::write(Compound *parent, Compound *compound) {
    Component *component = dynamic_cast<Component *>(compound);
    Component *mother = dynamic_cast<Component *>(parent);
    if (component) {
      Tag *tag = component->getTag();
      if (!tag) {
        // create component by name
        if (!isMotherCreated) {
          m_writer->writeln("constructor = Require \"libConstructor\")");
          m_writer->writeln("factory = constructor:getFactory()");
          m_writer->writeln("mother = factory:create(\"" + component->getName() + "\")");
          m_writer->writeln("constructor:setMother(mother)");
          m_writer->writeln("current = mother");
          isMotherCreated = true;
        }
        else {
          m_writer->writeln("component = factory:create(\"" + component->getName() + "\")");
          m_writer->writeln("current:add(component)\n");
        }
      }
      if (mother) {
        // insert commponent
      }
      if (!tag) {
        component->setTag(new Tag());
      }
    }
  }
}

