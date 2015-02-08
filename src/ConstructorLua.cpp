//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "Polycode.h"
#include "Components/Factory.hpp"

#define __MY_NAME "Synthetics.Constructor"

namespace Synthetics {
  namespace Constructor {
    typedef struct factory_s {
      Components::Factory *factory;
      Polycode::Core *core;
      Polycode::Scene *scene;
    } factory_t;

    static factory_t *checkFactory (lua_State *L) {
      void *ud = luaL_checkudata(L, 1, __MY_NAME);
      luaL_argcheck(L, ud != NULL, 1, "`factory' expected");
      return (factory_t *)ud;
    }

    static int getFactory(lua_State *L) {
      factory_t *factory = (factory_t *)lua_newuserdata(L, sizeof(factory_t));

      lua_getfield(L, LUA_REGISTRYINDEX, "core");
      factory->core = (Polycode::Core *)lua_touserdata(L, 1);
      lua_pop(L, 1);

      lua_getfield(L, LUA_REGISTRYINDEX, "scene");
      factory->scene = (Polycode::Scene *)lua_touserdata(L, 1);
      lua_pop(L, 1);

      lua_getfield(L, LUA_REGISTRYINDEX, "factory");
      factory->factory= (Components::Factory *)lua_touserdata(L, 1);
      lua_pop(L, 1);

      luaL_getmetatable(L, __MY_NAME);
      lua_setmetatable(L, -2);

      return 1;
    }

    static int factoryCreate(lua_State *L) {
      factory_t *factory = checkFactory(L);
      const char *name = luaL_checklstring(L, 2, NULL);
      return 0;
    }

    static const struct luaL_Reg funcs[] = {
      { "getFactory", getFactory },
      { NULL, NULL }
    };

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
    luaL_newmetatable(L, __MY_NAME);

    luaL_newmetatable(L, __MY_NAME);

    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);
    lua_settable(L, -3);

    luaL_openlib(L, NULL, Synthetics::Constructor::factoryMethods, 0);

    luaL_openlib(L, "Components.Factory", Synthetics::Constructor::funcs, 0);
    return 1;
  }
}
