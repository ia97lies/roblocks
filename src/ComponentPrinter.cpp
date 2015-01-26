//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "ComponentPrinter.hpp"

namespace Synthetics {

  ComponentPrinter::ComponentPrinter(Writer *writer) {
    /*
    isMotherCreated = false;
    */
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
        /*
        if (!isMotherCreated) {
          writer.writeln("constructor = Require \"libConstructor\")");
          writer.writeln("factory = constructor:getFactory()");
          writer.writeln("mother = factory:create(\""..component->getName().."\")");
          writer.writeln("constructor:setMother(mother)");
        }
        */
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

