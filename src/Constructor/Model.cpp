//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Model.hpp"

namespace Synthetics {
  namespace Constructor {
    Model::Model() {
      m_root = NULL;
      m_activeComponent = NULL;
      m_activePart = NULL;
      m_activePlug = NULL;
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

    void Model::activate(Polycode::Entity *shape) {
      Component *cur = m_root;
      if (cur) {
        for (int i = 0; i < cur->getNoParts(); i++) {
          for (int j = 0; j < cur->getPart(i)->getNoPlugs(); j++)  {
            if (cur->getPart(i)->getPlug(j)->getShape() == shape) {
              m_activeComponent = cur;
              m_activePart = cur->getPart(i);
              m_activePlug = cur->getPart(i)->getPlug(j);
            }
          }
        }
      }
    }

    Component *Model::getActiveComponent() {
      return m_activeComponent;
    }

    Part *Model::getActivePart() {
      return m_activePart;
    }

    Plug *Model::getActivePlug() {
      return m_activePlug;
    }

  }
}

