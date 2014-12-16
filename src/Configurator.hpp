//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONFIGURATOR_H
#define SYNTHETICS_CONFIGURATOR_H

#include "lua.hpp"
#include "PolycodeUnit.hpp"
#include "UnitFactory.hpp"

namespace Synthetics {

  class Configurator {
    public:
      Configurator(UnitFactory *factory);
      virtual ~Configurator();
      int getWidth();
      int getHeight();

    private:
      lua_State *m_L;
      int m_width;
      int m_height;
      typedef std::vector<PolycodeUnit *> *m_units;

      void error(const char *fmt, ...);
      void readWidth(); 
      void readHeight(); 
      int getNumber(const char *name); 
      void setLuaCPath(const char* path);
  };
}

#endif
