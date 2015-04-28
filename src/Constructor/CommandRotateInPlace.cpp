//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolyVector3.h"
#include "CommandRotateInPlace.hpp"

using namespace Polycode;

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
        rotate(m_direction);
      }
      return success;
    }

    void CommandRotateInPlace::undo() {
      rotate((-1) * m_direction);
    }

    void CommandRotateInPlace::rotate(int direction) {
      if (m_robot->getInPlace()) {
        Vector3 position = m_robot->getActivePlug()->getPosition();
        position.Normalize();
        Vector3 rotation =  m_robot->getInPlacePart()->getShape()->getRotationEuler();
        Vector3 rotate = position * 90 * direction;
        m_robot->getInPlacePart()->getShape()->setRotationEuler(rotation + rotate);
      }
    }

  }
}


