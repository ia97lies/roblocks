//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_COMMAND_ACTIVATE_H
#define SYNTHETICS_CONSTRUCTOR_COMMAND_ACTIVATE_H

#include "PolyEntity.h"
#include "Command.hpp"
#include "Robot.hpp"

namespace Synthetics {
  namespace Constructor {

    class CommandActivate : public Command {
      public:
        CommandActivate(Robot *robot, Polycode::Entity *plugShape); 
        virtual ~CommandActivate();
        virtual void execute();
        virtual void undo();

      private:
        Robot *m_robot;
        Polycode::Entity *m_plugShape;
        Polycode::Entity *m_prevPlugShape;
    };
  }
}

#endif
