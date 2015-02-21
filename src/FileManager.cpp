//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "FileManager.hpp"

using namespace Polycode;

namespace Synthetics {
  FileManager::FileManager(String workingDir, std::vector<String> extentions) : UIFileDialog::UIFileDialog(workingDir, false, extensions, false) {
  }

  FileManager::~FileManager() {
  }
}

