//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "CommandActivate.hpp"

namespace Synthetics {
  namespace Constructor {

    CommandActivate::CommandActivate(Robot *robot, Polycode::Entity *plugShape) {
      m_robot = robot;
      m_plugShape = plugShape;
      m_prevPlugShape = NULL;
    }

    CommandActivate::~CommandActivate() {}

    bool CommandActivate::execute() {
      Plug *plug = m_robot->getActivePlug();
      if (plug) {
        m_prevPlugShape = plug->getShape();
      }
      else {
        m_prevPlugShape = NULL;
      }
      m_robot->activate(m_plugShape);
      return true;
    }

    void CommandActivate::undo() {
      if (m_prevPlugShape) {
        m_robot->activate(m_prevPlugShape);
      }
      else {
        m_robot->deactivate(m_plugShape);
      }
    }
  }
}

