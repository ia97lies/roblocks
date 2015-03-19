//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_CONFIGURATOR_H
#define SYNTHETICS_CONFIGURATOR_H

#include "Lua.hpp"
#include "Components/Factory.hpp"

namespace Synthetics {

  class Configurator {
    public:
      Configurator(Components::Factory *factory);
      virtual ~Configurator();
      int getWidth();
      int getHeight();
      int getHistory(); 

    private:
      int m_width;
      int m_height;
      int m_history;
      Lua *m_lua;

      void readWidth(); 
      void readHeight(); 
      int getTableIntegerEntry(const char *name); 
  };
}

#endif
