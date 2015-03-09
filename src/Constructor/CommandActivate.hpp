//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_COMMAND_ACTIVATE_H
#define SYNTHETICS_CONSTRUCTOR_COMMAND_ACTIVATE_H

#include "Robot.hpp"

namespace Synthetics {
  namespace Constructor {

    class CommandActivate {
      public:
        CommandActivate(Robot *robot, Plug *plug); 
        virtual ~CommandActivate();
        virtual void execute();
        virtual void undo();

      private:
        Robot *m_robot;
        Plug *m_plug;
        Plug *m_previousPlug;
    };
  }
}

#endif
