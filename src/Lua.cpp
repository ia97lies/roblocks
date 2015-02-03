//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include <string>
#include "Lua.hpp"

namespace Synthetics {
  Lua::Lua() {
    m_L = NULL;
  }

  Lua::~Lua() {
    close();
  }

  void Lua::open() {
    m_L = luaL_newstate();
    luaL_openlibs(m_L);
  }

  void Lua::close() {
    if (m_L) {
      lua_close(m_L);
      m_L = NULL;
    }
  }

  void Lua::error(const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
  }

  void Lua::setCPath(const char* path) {
    lua_getglobal(m_L, "package");
    lua_getfield(m_L, -1, "cpath");
    std::string curPath = lua_tostring(m_L, -1);
    curPath.append(";");
    curPath.append(path);
    lua_pop(m_L, 1);
    lua_pushstring(m_L, curPath.c_str());
    lua_setfield(m_L, -2, "cpath");
    lua_pop(m_L, 1);
  }
}

