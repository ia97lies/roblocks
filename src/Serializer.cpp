//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Component.hpp"
#include "Serializer.hpp"

namespace Synthetics {
    class PrintComponent : public IterateMethod {
    public:
      PrintComponent(Writer *writer) {
        m_writer = writer;
      }

      virtual ~PrintComponent() {}

      virtual void call(Compound *compound) {
        Component *component = dynamic_cast<Component *>(compound);
        if (component ) {
          m_writer->write(component->getName() + "\n");
        }
      }

    private:
      Writer *m_writer;
  };

  Serializer::Serializer(Compound *compound, Writer *writer) {
    PrintComponent *method = new PrintComponent(writer);
    compound->iterate(method);
  }

  Serializer::~Serializer() {
  }
}

