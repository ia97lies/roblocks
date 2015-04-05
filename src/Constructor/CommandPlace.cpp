//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Components/Factory.hpp"
#include "CommandPlace.hpp"

namespace Synthetics {
  namespace Constructor {
    CommandPlace::CommandPlace(Robot *robot, Component *component) {
      m_robot = robot;
      m_component = component;
    }

    CommandPlace::~CommandPlace() {
      delete m_component;
    }

    void CommandPlace::execute() {
      m_robot->place(m_component);
      m_component = NULL;
    }

    void CommandPlace::undo() {
      m_component = m_robot->remove();
    }
  }
}


