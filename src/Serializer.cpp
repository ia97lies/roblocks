//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Component.hpp"
#include "Serializer.hpp"

namespace Synthetics {
    class PrintComponent : public IterateMethod {
    public:
      PrintComponent(Printer *printer) {
        m_printer = printer;
      }

      virtual ~PrintComponent() {}

      virtual void call(Compound *parent, Compound *compound) {
        if (m_printer) {
          m_printer->write(parent, compound);
        }
      }

    private:
      Printer *m_printer;
  };

  Serializer::Serializer(Compound *compound, Printer *printer) {
    if (compound) {
      PrintComponent *method = new PrintComponent(printer);
      compound->iterate(method);
    }
  }

  Serializer::~Serializer() {
  }
}

