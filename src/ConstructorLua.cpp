//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "Polycode.h"
#include "Components/Factory.hpp"

#define __FACTORY_NAME "Synthetics.Components.Factory"
#define __COMPONENT_NAME "Synthetics.Component"

namespace Synthetics {
  namespace Constructor {
    typedef struct factory_s {
      Components::Factory *factory;
      Polycode::Core *core;
      Polycode::Scene *scene;
    } factory_t;

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

    static const struct luaL_Reg funcs[] = {
      { "getFactory", getFactory },
      { NULL, NULL }
    };

    //------------------------------------------------------------------------
    typedef struct component_s { 
      Polycode::Core *core;
      Polycode::Scene *scene;
      Component *component;
    } component_t;

    static component_t *checkComponent (lua_State *L) {
      void *ud = luaL_checkudata(L, 1, __COMPONENT_NAME);
      luaL_argcheck(L, ud != NULL, 1, "`component' expected");
      return (component_t *)ud;
    }

    static int componentSelectPlug(lua_State *L) {
      component_t *component = checkComponent(L);
      return 0;
    }

    static const struct luaL_Reg componentMethods[] = {
      { "selectPlug", componentSelectPlug },
      { NULL, NULL }
    };

    //------------------------------------------------------------------------

    static factory_t *checkFactory (lua_State *L) {
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
  }
}

//----------------------------------------------------------------------------
// Shared library hook
//----------------------------------------------------------------------------
extern "C" {
  int luaopen_libConstructorLua(lua_State *L) {
    luaL_newmetatable(L, __FACTORY_NAME);

    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);
    lua_settable(L, -3);
    luaL_openlib(L, NULL, Synthetics::Constructor::factoryMethods, 0);

    luaL_openlib(L, "Components.Factory", Synthetics::Constructor::funcs, 0);
    return 1;
  }
}
