//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "Polycode.h"
#include "Robot.hpp"
#include "Components/Factory.hpp"

#define __FACTORY_NAME "Synthetics.Components.Factory"
#define __ROBOT_NAME "Synthetics.Components.Robot"
#define __PLUG_NAME "Synthetics.Plug"
#define __COMPONENT_NAME "Synthetics.Component"

using namespace Polycode;

namespace Synthetics {
  namespace Constructor {
    typedef struct factory_s {
      Components::Factory *factory;
      Polycode::Core *core;
      Polycode::Scene *scene;
    } factory_t;

    typedef struct robot_s {
      Robot *mother;
    } robot_t;

    //------------------------------------------------------------------------
    static int getFactory(lua_State *L) {
      lua_getfield(L, LUA_REGISTRYINDEX, "core");
      Polycode::Core *core = (Polycode::Core *)lua_touserdata(L, 1);
      lua_pop(L, 1);

      lua_getfield(L, LUA_REGISTRYINDEX, "scene");
      Polycode::Scene *scene = (Polycode::Scene *)lua_touserdata(L, 1);
      lua_pop(L, 1);

      lua_getfield(L, LUA_REGISTRYINDEX, "factory");
      Components::Factory *factory= (Components::Factory *)lua_touserdata(L, 1);
      lua_pop(L, 1);

      factory_t *newFactory = (factory_t *)lua_newuserdata(L, sizeof(factory_t));
      luaL_getmetatable(L, __FACTORY_NAME);
      lua_setmetatable(L, -2);

      newFactory->core = core;
      newFactory->scene = scene;
      newFactory->factory = factory;

      return 1;
    }

    static int getRobot(lua_State *L) {
      lua_getfield(L, LUA_REGISTRYINDEX, "robot");
      Robot *mother = (Robot *)lua_touserdata(L, 1);
      lua_pop(L, 1);

      robot_t *newRobot = (robot_t *)lua_newuserdata(L, sizeof(robot_t));
      luaL_getmetatable(L, __ROBOT_NAME);
      lua_setmetatable(L, -2);

      newRobot->mother = mother;

      return 1;
    }


    static const struct luaL_Reg funcs[] = {
      { "getFactory", getFactory },
      { "getRobot", getRobot },
      { NULL, NULL }
    };

    //------------------------------------------------------------------------
    typedef struct plug_s { 
      Plug *plug;
    } plug_t;

    static plug_t *checkPlug(lua_State *L, int pos) {
      void *ud = luaL_checkudata(L, pos, __PLUG_NAME);
      luaL_argcheck(L, ud != NULL, pos, "`plug' expected");
      return (plug_t *)ud;
    }

    static const struct luaL_Reg plugMethods[] = {
      { NULL, NULL }
    };

    //------------------------------------------------------------------------
    typedef struct component_s { 
      Polycode::Core *core;
      Polycode::Scene *scene;
      Component *component;
    } component_t;

    static component_t *checkComponent(lua_State *L, int pos) {
      void *ud = luaL_checkudata(L, pos, __COMPONENT_NAME);
      luaL_argcheck(L, ud != NULL, pos, "`component' expected");
      return (component_t *)ud;
    }

    static int componentGetPlug(lua_State *L) {
      component_t *component = checkComponent(L, 1);
      int plugIndex = luaL_checkinteger(L, 2);
      Plug *plug  = NULL;
      for (int i = 0; i < component->component->getNoParts(); i++) {
        Part *part = component->component->getPart(i);
        if (plugIndex >= part->getNoPlugs()) {
          plugIndex -= part->getNoPlugs();
        }
        else {
          plug = part->getPlug(plugIndex);
        }
      }
      lua_pop(L, 1);
      lua_pop(L, 1);
      if (plug) {
        plug_t *newPlug = (plug_t *)lua_newuserdata(L, sizeof(plug_t));
        luaL_getmetatable(L, __PLUG_NAME);
        lua_setmetatable(L, -2);
        newPlug->plug = plug;
      }
      else {
        luaL_error(L, "Plug not found");
      }
      return 1;
    }

    static int componentRotate(lua_State *L) {
      component_t *component = checkComponent(L, 1);
      float x = luaL_checknumber(L, 2);
      float y = luaL_checknumber(L, 3);
      float z = luaL_checknumber(L, 4);

      Part *part = component->component->getPart(0);
      part->getShape()->setRotationEuler(Vector3(x, y, z));

      return 0;
    }

    static const struct luaL_Reg componentMethods[] = {
      { "getPlug", componentGetPlug },
      { "rotate", componentRotate },
      { NULL, NULL }
    };

    //------------------------------------------------------------------------
    static factory_t *checkFactory(lua_State *L) {
      void *ud = luaL_checkudata(L, 1, __FACTORY_NAME);
      luaL_argcheck(L, ud != NULL, 1, "`factory' expected");
      return (factory_t *)ud;
    }

    static int factoryCreate(lua_State *L) {
      factory_t *factory = checkFactory(L);
      const char *name = luaL_checklstring(L, 2, NULL);
      Component *component = factory->factory->createComponent(name, factory->core, factory->scene);
      lua_pop(L, 1);
      lua_pop(L, 1);

      component_t *newComponent = (component_t *)lua_newuserdata(L, sizeof(component_t));
      luaL_getmetatable(L, __COMPONENT_NAME);
      lua_setmetatable(L, -2);

      newComponent->component = component;
      newComponent->core = factory->core;
      newComponent->scene = factory->scene;

      return 1;
    }

    static const struct luaL_Reg factoryMethods[] = {
      { "create", factoryCreate },
      { NULL, NULL }
    };

    //------------------------------------------------------------------------
    static robot_t *checkRobot(lua_State *L, int pos) {
      void *ud = luaL_checkudata(L, pos, __ROBOT_NAME);
      luaL_argcheck(L, ud != NULL, pos, "`robot' expected");
      return (robot_t *)ud;
    }

    static int robotInit(lua_State *L) {
      robot_t *roboter = checkRobot(L, 1);
      component_t *component = checkComponent (L, 2);
      roboter->mother->add(component->component);

      return 0;
    }

    static int robotActivate(lua_State *L) {
      robot_t *roboter = checkRobot(L, 1);
      plug_t *plug = checkPlug (L, 2);
      roboter->mother->activate(plug->plug->getShape());

      return 0;
    }

    static int robotPlace(lua_State *L) {
      robot_t *roboter = checkRobot(L, 1);
      component_t *component = checkComponent (L, 2);
      roboter->mother->place(component->component);

      return 0;
    }

    static int robotAdd(lua_State *L) {
      robot_t *roboter = checkRobot(L, 1);
      roboter->mother->add();

      return 0;
    }

    static const struct luaL_Reg robotMethods[] = {
      { "init", robotInit },
      { "activate", robotActivate },
      { "place", robotPlace },
      { "add", robotAdd },
      { NULL, NULL }
    };

  }
}

//----------------------------------------------------------------------------
// Shared library hook
//----------------------------------------------------------------------------
extern "C" {
  int luaopen_libRobotLua(lua_State *L) {
    luaL_newmetatable(L, __FACTORY_NAME);
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);
    lua_settable(L, -3);
    luaL_openlib(L, NULL, Synthetics::Constructor::factoryMethods, 0);

    luaL_newmetatable(L, __COMPONENT_NAME);
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);
    lua_settable(L, -3);
    luaL_openlib(L, NULL, Synthetics::Constructor::componentMethods, 0);

    luaL_newmetatable(L, __PLUG_NAME);
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);
    lua_settable(L, -3);
    luaL_openlib(L, NULL, Synthetics::Constructor::plugMethods, 0);

    luaL_newmetatable(L, __ROBOT_NAME);
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);
    lua_settable(L, -3);
    luaL_openlib(L, NULL, Synthetics::Constructor::robotMethods, 0);

    luaL_openlib(L, "Components.Factory", Synthetics::Constructor::funcs, 0);
    return 1;
  }
}

