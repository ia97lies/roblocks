//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONSTRUCTOR_COMMAND_SET_ROOT_H
#define SYNTHETICS_CONSTRUCTOR_COMMAND_SET_ROOT_H

namespace Synthetics {
  namespace Constructor {

    class CommandSetRoot {
      CommandSetRoot(); 
      virtual ~CommandSetRoot();
      virtual void execute();
      virtual void undo();
    };
  }
}

#endif
