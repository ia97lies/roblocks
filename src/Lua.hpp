//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_LUA_H
#define SYNTHETICS_LUA_H

#include "lua.hpp"

namespace Synthetics {

  class Lua {
    public:
      Lua();
      virtual ~Lua();
      void open();
      void close();
      void error(const char *fmt, ...);
      void setCPath(const char* path);

    protected:
      lua_State *m_L;
  };
}

#endif
