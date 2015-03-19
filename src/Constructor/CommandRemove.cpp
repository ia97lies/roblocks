//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Polycode.h"
#include "Components/Factory.hpp"
#include "CommandRemove.hpp"

namespace Synthetics {
  namespace Constructor {

    CommandRemove::CommandRemove(Robot *robot, Polycode::Core *core, Polycode::Scene *scene) {
      m_robot = robot;
      m_component = NULL;
      m_activePlug = NULL;
    }

    CommandRemove::~CommandRemove() {
      if (m_component) {
        delete m_component;
      }
    }

    void CommandRemove::execute() {
      if (m_robot->getInPlace()) {
        m_component = m_robot->remove();
      }
      else {
        m_activePlug = m_robot->getActivePlug();
        m_component = m_robot->remove();
        m_robot->place(m_component);
        m_component = NULL;
      }
    }

    void CommandRemove::undo() {
      if (!m_robot->getInPlace()) {
        m_robot->place(m_component);
        m_component = NULL;
      }
      else {
        m_robot->add();
        m_component = NULL;
      }
    }
  }
}


