//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_FILE_MANAGER_H
#define SYNTHETICS_FILE_MANAGER_H

#include "PolyUIFileDialog.h"
#include "Components/Factory.hpp"
#include "Robot.hpp"

using namespace Polycode;

namespace Synthetics {
  class FileManagerCompletion {
    public:
      virtual ~FileManagerCompletion() {}
      virtual void done() = 0;
  };

  class FileManager : public Polycode::UIFileDialog {
    public:
      FileManager(Polycode::Core *core, Polycode::PhysicsScene *scene, Components::Factory *factory, 
                  std::vector<Polycode::String> extentions);
      virtual ~FileManager();

      virtual void onClose();
      virtual void handleEvent(Event *e);
      //XXX I AM HERE

      virtual void save(Robot *robot, FileManagerCompletion *completion); 
      virtual void load(Robot *robot, FileManagerCompletion *completion);
    private:
      Robot *m_robot;
      Polycode::Core *m_core;
      Polycode::Scene *m_scene;
      Components::Factory *m_factory;
      FileManagerCompletion *m_saveCompletion;
      FileManagerCompletion *m_loadCompletion;
      Polycode::UITextInput *m_fileNameInput; 

      void saveComplete();
      void loadComplete();
      void cancel();
  };
}

#endif
