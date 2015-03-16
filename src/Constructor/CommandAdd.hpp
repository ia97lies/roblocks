//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_COMMAND_ADD_H
#define SYNTHETICS_CONSTRUCTOR_COMMAND_ADD_H

#include "Command.hpp"
#include "Robot.hpp"

namespace Synthetics {
  namespace Constructor {

    class CommandAdd : public Command {
      public:
        CommandAdd(Robot *robot, Component *component, Polycode::Core *core, Polycode::Scene *scene); 
        virtual ~CommandAdd();
        virtual void execute();
        virtual void undo();

      private:
        Robot *m_robot;
        Component *m_component;
        std::string m_name; 
        Polycode::Core *m_core;
        Polycode::Scene *m_scene;
        Plug *m_activePlug;
    };
  }
}

#endif
