//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_COMMAND_ADD_H
#define SYNTHETICS_CONSTRUCTOR_COMMAND_ADD_H

#include "Robot.hpp"

namespace Synthetics {
  namespace Constructor {

    class CommandAdd {
      public:
        CommandAdd(Robot *robot, Component *component); 
        virtual ~CommandAdd();
        virtual void execute();
        virtual void undo();

      private:
        Robot *m_robot;
        Component *m_component;
        Plug *m_activePlug;
    };
  }
}

#endif
