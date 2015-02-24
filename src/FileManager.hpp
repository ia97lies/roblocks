//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_FILE_MANAGER_H
#define SYNTHETICS_FILE_MANAGER_H

#include "PolyUIFileDialog.h"
#include "Robot.hpp"

using namespace Polycode;

namespace Synthetics {
  class FileManagerCompletion {
    virtual ~FileManagerCompletion();
    virtual void done(Robot *robot) = 0;
  };

  class FileManager : public Polycode::UIFileDialog {
    public:
      FileManager(Polycode::String workingDir, std::vector<Polycode::String> extentions);
      virtual ~FileManager();

      virtual void onClose();
      virtual void handleEvent(Event *e);

      virtual void save(Robot *robot, FileManagerCompletion *completion); 
      virtual void load(FileManagerCompletion *completion);
    private:
      Robot *m_robot;
      FileManagerCompletion *m_completion;
  };
}

#endif
