//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "Compounds/Factory.hpp"
#include "Compounds/Passive/Hub.hpp"

using namespace Polycode;
namespace Synthetics {
  namespace Compounds {
    namespace Passive {

      //--------------------------------------------------------------------------
      // Compounds interface
      //--------------------------------------------------------------------------
      Hub::Hub() {
        fprintf(stderr, "Create Hub\n");
      }

      Hub::~Hub() {
        fprintf(stderr, "Destroy Hub\n");
      }

      //----------------------------------------------------------------------
      // Compounds factory
      //----------------------------------------------------------------------
      Compound *HubCreator() {
        Hub *hub = new Hub();
        return hub;
      }

      static int HubRegister(lua_State *L) {
        lua_getfield(L, LUA_REGISTRYINDEX, "factory");
        Compounds::Factory *factory = (Compounds::Factory *)lua_touserdata(L, 1);
        lua_pop(L, 1);
        factory->addCreator("Passive.Hub", &HubCreator);
        return 0;
      }

      static const struct luaL_Reg HubFuncs[] = {
        { "register", HubRegister },
        { NULL, NULL }
      };
    }
  }
}

//----------------------------------------------------------------------------
// Shared library hook
//----------------------------------------------------------------------------
extern "C" {
  int luaopen_libPassiveHub(lua_State *L) {
    luaL_register(L, "Passive.Hub", Synthetics::Compounds::Passive::HubFuncs);
    return 1;
  }
}
