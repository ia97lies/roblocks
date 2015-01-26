//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Components/Factory.hpp"
#include "ComponentPrinter.hpp"

namespace Synthetics {

  ComponentPrinter::ComponentPrinter(Components::Factory *factory, Writer *writer) {
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

