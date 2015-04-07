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

    bool CommandPlace::execute() {
      bool success = false;
      m_robot->place(m_component);
      if (m_component == m_robot->getInPlace()) {
        success = true;
      }
      m_component = NULL;
      return success;
    }

    void CommandPlace::undo() {
      m_component = m_robot->remove();
    }
  }
}


