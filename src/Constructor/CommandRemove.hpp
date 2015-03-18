//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_COMMAND_REMOVE_H
#define SYNTHETICS_CONSTRUCTOR_COMMAND_REMOVE_H

#include "Command.hpp"
#include "Robot.hpp"

namespace Synthetics {
  namespace Constructor {

    class CommandRemove : public Command {
      public:
        CommandRemove(Robot *robot, Polycode::Core *core, Polycode::Scene *scene); 
        virtual ~CommandRemove();
        virtual void execute();
        virtual void undo();

      private:
        Robot *m_robot;
        Component *m_component;
    };
  }
}

#endif
