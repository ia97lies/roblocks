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
        bool m_isNone;
        bool m_isInPlace;
        Robot *m_robot;
        Polycode::Vector3 m_rotation;
        std::string m_name; 
        Polycode::Core *m_core;
        Polycode::Scene *m_scene;
    };
  }
}

#endif
