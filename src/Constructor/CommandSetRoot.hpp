//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_COMMAND_SET_ROOT_H
#define SYNTHETICS_CONSTRUCTOR_COMMAND_SET_ROOT_H

#include "Robot.hpp"

namespace Synthetics {
  namespace Constructor {

    class CommandSetRoot {
      public:
        CommandSetRoot(Robot *robot, Component *component); 
        virtual ~CommandSetRoot();
        virtual void execute();
        virtual void undo();

      private:
        Robot *m_robot;
        Component *m_component;
    };
  }
}

#endif