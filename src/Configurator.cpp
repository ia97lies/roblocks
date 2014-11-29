//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "UnitFactory.hpp"
#include "Configurator.hpp"

namespace Synthetics {

  //--------------------------------------------------------------------------
  // public:
  //--------------------------------------------------------------------------
  Configurator::Configurator(UnitFactory *factory) {
    m_width = 640;
    m_height = 480;
    m_L = luaL_newstate();
    luaL_openlibs(m_L);

    setLuaCPath("./lib/?.so");
    lua_pushlightuserdata(m_L, factory);
    lua_setfield(m_L, LUA_REGISTRYINDEX, "factory");

    if (luaL_loadfile(m_L, "Resources/synthetics.conf") || lua_pcall(m_L, 0, 0, 0)) {
      error("cannot load Resources/synthetics.conf: %s\n", lua_tostring(m_L, -1));
    }

    lua_getglobal(m_L, "window");
    if (!lua_istable(m_L, -1)) {
      error("window is not a valid directive, try window = { width = 640, height = 480 }");
    }
    else {
      readWidth();
      readHeight();
    }

    factory->createUnit("Passive.Block", NULL, NULL);
  }

  Configurator::~Configurator() {
    if (m_L) {
      lua_close(m_L);
    }
  }

  int Configurator::getWidth() {
    return m_width;
  }

  int Configurator::getHeight() {
    return m_height;
  }

  //--------------------------------------------------------------------------
  // private:
  //--------------------------------------------------------------------------
  void Configurator::error(const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
  }

  void Configurator::readWidth() {
    m_width = getNumber("width");
  }

  void Configurator::readHeight() {
    m_height = getNumber("height");
  }

  int Configurator::getNumber(const char *name) {
    int result;
    lua_pushstring(m_L, name);
    lua_gettable(m_L, -2);
    if (!lua_isnumber(m_L, -1)) {
      error("expect a number value");
    }
    result = (int) lua_tonumber(m_L, -1);
    lua_pop(m_L, 1);
    return result;
  }

  void Configurator::setLuaCPath(const char* path) {
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

