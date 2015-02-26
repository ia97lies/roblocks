//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "FileManager.hpp"
#include "Constructor.hpp"

using namespace Polycode;

namespace Synthetics {
  //--------------------------------------------------------------------------
  class Save : public IterateMethod {
    public:
      Save(FILE *fp) { 
        m_fp = fp;
      }

      virtual ~Save() {}

      virtual void call(Compound *parentCompound, Compound *compound) {
        Component *component = dynamic_cast<Component *>(compound);
        if (component) {
          Component *parent= dynamic_cast<Component *>(parentCompound);
          if (parent) {
            int parentPlugId = 0;
            Plug *childPlug;
            int p = 0;
            for (int i = 0; i < parent->getNoParts(); i++) {
              Part *part = parent->getPart(i);
              for (int j = 0; j < part->getNoPlugs(); j++, p++) {
                Plug *plug = part->getPlug(j)->getConnectedPlug();
                if (plug && plug->getParent() == component) {
                  childPlug = plug;
                  parentPlugId = p;
                }
              }
            }
            int childPlugId = 0;
            p = 0;
            for (int i = 0; i < component->getNoParts(); i++) {
              Part *part = component->getPart(i);
              for (int j = 0; j < part->getNoPlugs(); j++, p++) {
                Plug *plug = part->getPlug(j);
                if (plug == childPlug) {
                  childPlugId = p;
                }
              }
            }
            Part *part = component->getPart(0);
            Vector3 rotation = part->getShape()->getRotationEuler(); 

            fprintf(m_fp, "plug = component%ld:getPlug(%d)\n", parent->getId(), parentPlugId);
            fprintf(m_fp, "mother:activate(plug)\n");
            fprintf(m_fp, "component%ld = factory:create(\"%s\")\n", component->getId(), component->getName().c_str());
            fprintf(m_fp, "mother:place(component%ld)\n", component->getId());
            fprintf(m_fp, "component%ld:rotate(%f, %f, %f)\n", component->getId(), rotation.x, rotation.y, rotation.z);
            fprintf(m_fp, "plug = component%ld:getPlug(%d)\n", component->getId(), childPlugId);
            fprintf(m_fp, "mother:add()\n");
          }
          else {
            fprintf(m_fp, "component%ld = factory:create(\"Passive.Hub\")\n", component->getId());
            fprintf(m_fp, "mother:init(component%ld)\n", component->getId());
          }
        }
      }

    private:
      FILE *m_fp;
  };

  //--------------------------------------------------------------------------
  FileManager::FileManager(String workingDir, std::vector<String> extentions) 
    : UIFileDialog::UIFileDialog(workingDir, false, extensions, false) {
    m_robot = NULL;
    m_saveCompletion = NULL;
    m_loadCompletion = NULL;
    m_fileNameInput = new UITextInput(false, 270, 12); 
    addChild(m_fileNameInput); 
    m_fileNameInput->addEventListener(this, UIEvent::CHANGE_EVENT);
    m_fileNameInput->setPosition(100, 5);
    m_fileNameInput->setText(selection.c_str());
    hideWindow();
  }

  FileManager::~FileManager() {
  }

  void FileManager::cancel() {
    saveComplete();
    loadComplete();
  }

  void FileManager::saveComplete() {
    if (m_saveCompletion) {
      m_saveCompletion->done();
      delete m_saveCompletion;
      m_saveCompletion = NULL;
    }
  }

  void FileManager::loadComplete() {
    if (m_loadCompletion) {
      m_loadCompletion->done();
      delete m_loadCompletion;
      m_loadCompletion = NULL;
    }
  }

  void FileManager::onClose() {
    cancel();
    hideWindow();
  }

  void FileManager::handleEvent(Event *e) {
    UIFileDialog::handleEvent(e);
    if (e->getEventCode() == InputEvent::EVENT_DOUBLECLICK) {
      fprintf(stderr, "Got a double click\n");
      m_fileNameInput->setText(selection.c_str());
    }

    else if (e->getEventType() == "UIEvent") {
      if(e->getEventCode() == UIEvent::CLICK_EVENT) {
        if(e->getDispatcher() == okButton && m_robot) {
          hideWindow();
          FILE *fp = fopen(m_fileNameInput->getText().c_str(), "w");
          fprintf(stderr, "XXX %p, %s\n", fp, m_fileNameInput->getText().c_str());

          // open .snapshot.lua
          fprintf(fp, "robot = require \"libRobotLua\"\n");
          fprintf(fp, "factory = robot.getFactory()\n");
          fprintf(fp, "mother = robot.getRobot()\n");

          Save *method = new Save(fp);
          m_robot->iterate(method);
          loadComplete();
        }
        if(e->getDispatcher() == cancelButton) {
          cancel();
          hideWindow();
        }
      }
    }
  }

  void FileManager::save(Robot *robot, FileManagerCompletion *completion) {
    showWindow();
    m_robot = robot;
    m_saveCompletion = completion;
  }

  void FileManager::load(Robot *robot, FileManagerCompletion *completion) {
    showWindow();
    m_loadCompletion = completion;
  }
}

