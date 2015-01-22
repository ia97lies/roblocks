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
        if (m_writer) {
          m_writer->write(compound);
        }
      }

    private:
      Writer *m_writer;
  };

  Serializer::Serializer(Compound *compound, Writer *writer) {
    if (compound) {
      PrintComponent *method = new PrintComponent(writer);
      compound->iterate(method);
    }
  }

  Serializer::~Serializer() {
  }
}

