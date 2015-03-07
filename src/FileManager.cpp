//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Lua.hpp"
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
            fprintf(m_fp, "root:activate(plug)\n");
            fprintf(m_fp, "component%ld = factory:create(\"%s\")\n", component->getId(), component->getName().c_str());
            fprintf(m_fp, "root:place(component%ld)\n", component->getId());
            fprintf(m_fp, "component%ld:rotate(%f, %f, %f)\n", component->getId(), rotation.x, rotation.y, rotation.z);
            fprintf(m_fp, "plug = component%ld:getPlug(%d)\n", component->getId(), childPlugId);
            fprintf(m_fp, "root:add()\n");
          }
          else {
            fprintf(m_fp, "component%ld = factory:create(\"Passive.Hub\")\n", component->getId());
            fprintf(m_fp, "root:init(component%ld)\n", component->getId());
          }
        }
      }

    private:
      FILE *m_fp;
  };

  //--------------------------------------------------------------------------
  FileManager::FileManager(Core *core, PhysicsScene *scene, Components::Factory *factory, std::vector<String> extentions) 
    : UIFileDialog::UIFileDialog(core->getDefaultWorkingDirectory(), false, extensions, false) {
    m_robot = NULL;
    m_core = core;
    m_scene = scene;
    m_factory = factory;
    m_saveCompletion = NULL;
    m_loadCompletion = NULL;
    m_fileNameInput = new UITextInput(false, 270, 12); 
    addChild(m_fileNameInput); 
    m_fileNameInput->addEventListener(this, UIEvent::CHANGE_EVENT);
    m_fileNameInput->setPosition(100, 5);
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
      m_fileNameInput->setText(selection.c_str());
    }

    else if (e->getEventType() == "UIEvent") {
      if(e->getEventCode() == UIEvent::CLICK_EVENT) {
        if(e->getDispatcher() == okButton && m_saveCompletion) {
          hideWindow();
          FILE *fp = fopen(m_fileNameInput->getText().c_str(), "w");

          // open .snapshot.lua
          fprintf(fp, "robot = require \"libRobotLua\"\n");
          fprintf(fp, "factory = robot.getFactory()\n");
          fprintf(fp, "root = robot.getRobot()\n");

          Save *method = new Save(fp);
          m_robot->iterate(method);
          saveComplete();
        }
        else if(e->getDispatcher() == okButton && m_loadCompletion) {
          if (selection.size() > 0) {
            hideWindow();
            Lua *lua = new Lua();
            lua->open();
            lua->setCPath("./lib/?.so");
            lua_State *L = lua->L();
            lua_pushlightuserdata(L, m_core);
            lua_setfield(L, LUA_REGISTRYINDEX, "core");
            lua_pushlightuserdata(L, m_scene);
            lua_setfield(L, LUA_REGISTRYINDEX, "scene");
            lua_pushlightuserdata(L, m_factory);
            lua_setfield(L, LUA_REGISTRYINDEX, "factory");
            lua_pushlightuserdata(L, m_robot);
            lua_setfield(L, LUA_REGISTRYINDEX, "robot");

            if (luaL_loadfile(L, m_fileNameInput->getText().c_str()) || lua_pcall(L, 0, 0, 0)) {
              lua->error("cannot load %s: %s\n", m_fileNameInput->getText().c_str(), lua_tostring(L, -1));
            }
            delete lua;
            loadComplete();
          }
        }
        else if(e->getDispatcher() == cancelButton) {
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
    // TODO: for windows it needs to be a \ instead of a / is there a proper way?
    selection = currentFolderPath + "/newfile.lua";
    m_fileNameInput->setText(selection);
  }

  void FileManager::load(Robot *robot, FileManagerCompletion *completion) {
    showWindow();
    m_robot = robot;
    m_loadCompletion = completion;
  }
}

