//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONFIGURATOR_H
#define SYNTHETICS_CONFIGURATOR_H

#include "lua.hpp"
#include "Unit.hpp"
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
      Polycode::ScenePrimitive * m_marker; 
      int m_width;
      int m_height;
      typedef std::vector<Unit *> *m_units;

      void error(const char *fmt, ...);
      void readWidth(); 
      void readHeight(); 
      int getNumber(const char *name); 
      void setLuaCPath(const char* path);
  };
}

#endif
