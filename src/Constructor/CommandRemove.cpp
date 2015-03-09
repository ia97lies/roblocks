//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "CommandRemove.hpp"

namespace Synthetics {
  namespace Constructor {
    CommandRemove::CommandRemove(Robot *robot, Component *component) {
      m_robot = robot;

    }

    CommandRemove::~CommandRemove() {}

    void CommandRemove::execute() {
      m_robot->remove();
    }

    void CommandRemove::undo() {
    }
  }
}


