//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Model.hpp"

namespace Synthetics {
  namespace Constructor {
    Model::Model() {
      m_root = NULL;
    }

    Model::~Model() {
      delete m_root;
    }

    void Model::setRoot(Component *component) {
      m_root = component;
    }

    Component *Model::getRoot() {
      return m_root;
    }

  }
}

