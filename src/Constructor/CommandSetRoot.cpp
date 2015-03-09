//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "CommandSetRoot.hpp"

namespace Synthetics {
  namespace Constructor {

    CommandSetRoot::CommandSetRoot(Robot *robot, Component *component) {
      m_robot = robot;
      m_component = component;
    }
    CommandSetRoot::~CommandSetRoot() {}
    void CommandSetRoot::execute() {
      m_robot->setRoot(m_component);
    }
    void CommandSetRoot::undo() {
      // select one plug no mather which one
      Plug *plug = m_component->getPart(0)->getPlug(0);
      m_robot->activate(plug->getShape());
      m_robot->remove();
    }
  }
}

