//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Components/Factory.hpp"
#include "CommandSetRoot.hpp"

namespace Synthetics {
  namespace Constructor {

    CommandSetRoot::CommandSetRoot(Robot *robot, Component *component) {
      m_robot = robot;
      m_component = component;
    }

    CommandSetRoot::~CommandSetRoot() {
      delete m_deletable;
    }

    bool CommandSetRoot::execute() {
      m_robot->setRoot(m_component);
      m_deletable = NULL;
    }

    void CommandSetRoot::undo() {
      m_robot->activate(m_component->getPart(0)->getPlug(0)->getShape());
      m_component = m_robot->remove();
      m_component->getPart(0)->getPlug(0)->activate(false);
      m_deletable = m_component;
    }
  }
}

