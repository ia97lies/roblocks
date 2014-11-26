//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONFIGURATOR_H
#define SYNTHETICS_CONFIGURATOR_H

#include "lua.hpp"

namespace Synthetics {

  class Configurator {
    public:
      Configurator();
      virtual ~Configurator();
    private:
      lua_State *m_L;
  };

}

#endif
