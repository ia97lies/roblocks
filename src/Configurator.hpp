//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONFIGURATOR_H
#define SYNTHETICS_CONFIGURATOR_H

#include "lua.hpp"
#include "Unit.hpp"

namespace Synthetics {

  class Configurator {
    public:
      Configurator();
      virtual ~Configurator();
      int getWidth();
      int getHeight();

    private:
      lua_State *m_L;
      int m_width;
      int m_height;
      typedef std::vector<Unit *> *m_units;

      void error(const char *fmt, ...);
      void readWidth(); 
      void readHeight(); 
      int getNumber(const char *name); 
  };
}

#endif
