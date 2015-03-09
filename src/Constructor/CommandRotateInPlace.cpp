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

    void CommandRotateInPlace::execute() {
      m_robot->rotateInPlace(m_direction);
    }

    void CommandRotateInPlace::undo() {
      m_robot->rotateInPlace((-1) * m_direction);
    }
  }
}


