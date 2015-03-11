//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "CommandRemove.hpp"

namespace Synthetics {
  namespace Constructor {
    CommandRemove::CommandRemove(Robot *robot, Component *component) {
      m_robot = robot;
      // TODO: have to store rotation and name of component
      //       need the factory to recreate on undo.
      //       Refactor the factory and handover core and scene on instantiation
    }

    CommandRemove::~CommandRemove() {}

    void CommandRemove::execute() {
      m_robot->remove();
    }

    void CommandRemove::undo() {
    }
  }
}


