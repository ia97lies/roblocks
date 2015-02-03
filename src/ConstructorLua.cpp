//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "Polycode.h"

#define __MY_NAME "Constructor"

namespace Synthetics {
  //----------------------------------------------------------------------
  // Lua Register
  //----------------------------------------------------------------------
  static int ConstructorDummy(lua_State *L) {
    return 0;
  }

  static const struct luaL_Reg ConstructorFuncs[] = {
    { "dummy", ConstructorDummy },
    { NULL, NULL }
  };
}

//----------------------------------------------------------------------------
// Shared library hook
//----------------------------------------------------------------------------
extern "C" {
  int luaopen_libConstructorLua(lua_State *L) {
    luaL_register(L, __MY_NAME, Synthetics::ConstructorFuncs);
    return 1;
  }
}
