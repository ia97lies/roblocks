//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_FILE_MANAGER_H
#define SYNTHETICS_FILE_MANAGER_H

#include "PolyUIFileDialog.h"

namespace Synthetics {
  class FileManager : public Polycode::UIFileDialog {
    public:
      FileManager(Polycode::String workingDir, std::vector<Polycode::String> extentions);
      virtual ~FileManager();
  };
}

#endif
