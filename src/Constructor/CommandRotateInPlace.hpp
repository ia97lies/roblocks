//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_COMMAND_ROTATE_IN_PLACE_H
#define SYNTHETICS_CONSTRUCTOR_COMMAND_ROTATE_IN_PLACE_H

#include "Command.hpp"
#include "Robot.hpp"

namespace Synthetics {
  namespace Constructor {

    class CommandRotateInPlace : public Command {
      public:
        CommandRotateInPlace(Robot *robot, int direction); 
        virtual ~CommandRotateInPlace();
        virtual bool execute();
        virtual void undo();

      private:
        Robot *m_robot;
        int m_direction;

        void rotate(int direction);
    };
  }
}

#endif
