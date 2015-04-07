//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Polycode.h"
#include "Components/Factory.hpp"
#include "CommandRemove.hpp"

namespace Synthetics {
  namespace Constructor {

    CommandRemove::CommandRemove(Robot *robot) {
      m_robot = robot;
      m_component = NULL;
      m_activePlug = NULL;
    }

    CommandRemove::~CommandRemove() {
      delete m_component;
    }

    void CommandRemove::execute() {
      m_activePlug = m_robot->getActivePlug();
      if (m_robot->getInPlace()) {
        m_component = m_robot->remove();
      }
      else {
        m_component = m_robot->remove();
        if (!m_robot->isEmpty()) {
          m_robot->place(m_component);
          m_component = NULL;
        }
      }
    }

    void CommandRemove::undo() {
      if (!m_robot->getInPlace() && !m_robot->isEmpty()) {
        m_robot->place(m_component);
      }
      else if (!m_robot->isEmpty()) {
        m_robot->add();
      }
      else {
        m_robot->setRoot(m_component);
      }
      if (m_activePlug) {
        m_robot->activate(m_activePlug->getShape());
      }
      m_component = NULL;
    }
  }
}


