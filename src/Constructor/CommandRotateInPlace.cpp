//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "CommandRotateInPlace.hpp"

namespace Synthetics {
  namespace Constructor {
    CommandRotateInPlace::CommandRotateInPlace(Robot *robot, int direction) {
      m_robot = robot;
      m_direction = direction;
    }

    CommandRotateInPlace::~CommandRotateInPlace() {}

    bool CommandRotateInPlace::execute() {
      bool success = false;
      if (m_robot->getInPlace() != NULL) {
        success = true;
        m_robot->rotateInPlace(m_direction);
      }
      return success;
    }

    void CommandRotateInPlace::undo() {
      m_robot->rotateInPlace((-1) * m_direction);
    }
  }
}


