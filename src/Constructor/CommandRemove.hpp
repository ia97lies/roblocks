//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_COMMAND_REMOVE_H
#define SYNTHETICS_CONSTRUCTOR_COMMAND_REMOVE_H

#include "Robot.hpp"

namespace Synthetics {
  namespace Constructor {

    class CommandRemove {
      public:
        CommandRemove(Robot *robot, Component *component); 
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
