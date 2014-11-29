//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "UnitFactory.hpp"
#include "Units/Passive/Block.hpp"

using namespace Polycode;
namespace Synthetics {
  namespace Units {
    namespace Passive {

      //--------------------------------------------------------------------------
      // public:
      //--------------------------------------------------------------------------
      Block::Block(Core *core, Scene *scene) {
        fprintf(stderr, "Create a passive block\n");
      }

      Block::~Block() {
      }

      int Block::noOfFaces() {
        return 0;
      }

      Vector3 Block::getOrientation(int face) {
        return Vector3(0, 0, 0);
      }

      void Block::addUnit(int face, Unit *unit) {
      }

      Unit *Block::getUnit(int face) {
        return NULL;
      }

      void Block::handleEvent(Event *event) {
      }

      Unit *BlockCreator(Polycode::Core *core, Polycode::Scene *scene) {
        return new Block(core, scene);
      }

      static int BlockRegister(lua_State *L) {
        lua_getfield(L, LUA_REGISTRYINDEX, "factory");
        UnitFactory *factory = (UnitFactory *)lua_touserdata(L, 1);
        lua_pop(L, 1);
        factory->addCreator("Passive.Block", &Passive::BlockCreator);
        return 0;
      }

      static const struct luaL_Reg BlockFuncs[] = {
        { "register", BlockRegister },
        { NULL, NULL }
      };
    }
  }
}

extern "C" {
  int luaopen_libPassiveBlock(lua_State *L) {
    luaL_register(L, "Passive.Block", Synthetics::Units::Passive::BlockFuncs);
    return 1;
  }
}
