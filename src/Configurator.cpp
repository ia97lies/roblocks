//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Components/Factory.hpp"
#include "Configurator.hpp"

namespace Synthetics {

  //--------------------------------------------------------------------------
  // public:
  //--------------------------------------------------------------------------
  Configurator::Configurator(Components::Factory *factory) {
    m_width = 640;
    m_height = 480;

    Lua *m_lua = new Lua();
    m_lua->open();
    m_lua->setCPath("./lib/?.so");

    lua_State *L = m_lua->L();
    lua_pushlightuserdata(L, factory);
    lua_setfield(L, LUA_REGISTRYINDEX, "factory");

    if (luaL_loadfile(L, "Resources/synthetics.conf") || lua_pcall(L, 0, 0, 0)) {
      m_lua->error("cannot load Resources/synthetics.conf: %s\n", lua_tostring(L, -1));
    }

    lua_getglobal(L, "window");
    if (!lua_istable(L, -1)) {
      m_lua->error("window is not a valid directive, try window = { width = 640, height = 480 }");
    }
    else {
      readWidth();
      readHeight();
    }
  }

  Configurator::~Configurator() {
    delete m_lua;
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
  void Configurator::readWidth() {
    m_width = getNumber("width");
  }

  void Configurator::readHeight() {
    m_height = getNumber("height");
  }

  int Configurator::getNumber(const char *name) {
    int result;
    lua_State *L = m_lua->L();
    lua_pushstring(L, name);
    lua_gettable(L, -2);
    if (!lua_isnumber(L, -1)) {
      m_lua->error("expect a number value");
    }
    result = (int) lua_tonumber(L, -1);
    lua_pop(L, 1);
    return result;
  }
}

