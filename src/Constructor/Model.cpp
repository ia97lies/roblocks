//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Model.hpp"

namespace Synthetics {
  namespace Constructor {
    class FindActive : public IterateMethod {
      public:
        FindActive(Polycode::Entity *plugShape) { 
          activeComponent = NULL;
          activePart = NULL;
          activePlug = NULL;
          m_plugShape = plugShape; 
        }

        virtual ~FindActive() {}

        virtual void call(Compound *parent, Compound *compound) {
          Component *cur = dynamic_cast<Component *>(compound);
          if (cur) {
            for (int i = 0; i < cur->getNoParts(); i++) {
              for (int j = 0; j < cur->getPart(i)->getNoPlugs(); j++)  {
                if (cur->getPart(i)->getPlug(j)->getShape() == m_plugShape) {
                  activeComponent = cur;
                  activePart = cur->getPart(i);
                  activePlug = cur->getPart(i)->getPlug(j);
                }
              }
            }
          }
        }

        Component *activeComponent;
        Part *activePart;
        Plug *activePlug;

      private:
        Polycode::Entity *m_plugShape;
    };

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
      if (m_root) {
        FindActive *method = new FindActive(shape);
        m_root->iterate(method);
        m_activeComponent = method->activeComponent;
        m_activePart = method->activePart;
        m_activePlug = method->activePlug;
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

