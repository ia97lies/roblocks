//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Components/Factory.hpp"
#include "CommandSetRoot.hpp"

namespace Synthetics {
  namespace Constructor {

    CommandSetRoot::CommandSetRoot(Robot *robot, Component *component, Polycode::Core *core, Polycode::Scene *scene) {
      m_robot = robot;
      m_component = component;
      m_name = component->getName();
      m_scene = scene;
      m_activePlug = NULL;
    }

    CommandSetRoot::~CommandSetRoot() {
      delete m_component;
    }

    void CommandSetRoot::execute() {
      m_robot->setRoot(m_component);
      if (m_activePlug) {
        m_robot->activate(m_activePlug->getShape());
      }
      else {
        m_activePlug = m_component->getPart(0)->getPlug(0);
      }
      m_component = NULL;
    }

    void CommandSetRoot::undo() {
      m_robot->activate(m_activePlug->getShape());
      m_component = m_robot->remove();
    }
  }
}

