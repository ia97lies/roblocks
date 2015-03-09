//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "CommandActivate.hpp"

namespace Synthetics {
  namespace Constructor {

    CommandActivate::CommandActivate(Robot *robot, Plug *plug) {
      m_robot = robot;
      m_plug = plug;
      m_previousPlug = NULL;
    }

    CommandActivate::~CommandActivate() {}

    void CommandActivate::execute() {
      m_previousPlug = m_robot->getActivePlug();
      m_robot->activate(m_plug->getShape());
    }

    void CommandActivate::undo() {
      if (m_previousPlug) {
        m_robot->activate(m_previousPlug->getShape());
      }
    }
  }
}

