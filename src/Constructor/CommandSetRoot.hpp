//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_COMMAND_SET_ROOT_H
#define SYNTHETICS_CONSTRUCTOR_COMMAND_SET_ROOT_H

#include "Command.hpp"
#include "Robot.hpp"

namespace Synthetics {
  namespace Constructor {

    class CommandSetRoot : public Command {
      public:
        CommandSetRoot(Robot *robot, Component *component, Polycode::Core *core, Polycode::Scene *scene); 
        virtual ~CommandSetRoot();
        virtual void execute();
        virtual void undo();

      private:
        Robot *m_robot;
        Component *m_component;
        std::string m_name; 
        Polycode::Scene *m_scene;
        Plug *m_activePlug;
    };
  }
}

#endif
