//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "CommandPlace.hpp"

namespace Synthetics {
  namespace Constructor {
    CommandPlace::CommandPlace(Robot *robot, Component *component) {
      m_robot = robot;
      m_component = component;
    }

    CommandPlace::~CommandPlace() {}

    void CommandPlace::execute() {
      m_robot->place(m_component);
    }

    void CommandPlace::undo() {
    }
  }
}


