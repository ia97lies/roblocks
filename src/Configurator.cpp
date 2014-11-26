//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Configurator.hpp"

namespace Synthetics {

  Configurator::Configurator() {
    m_L = luaL_newstate();
    luaL_openlibs(m_L);
    if (luaL_loadfile(m_L, "Resources/synthetics.conf") || lua_pcall(m_L, 0, 0, 0)) {
      fprintf(stderr, "cannot load Resources/synthetics.conf: %s\n", lua_tostring(m_L, -1));
    }
  }

  Configurator::~Configurator() {
    lua_close(m_L);
  }

}

