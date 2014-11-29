//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "PassiveBlock.hpp"

using namespace Polycode;
namespace Synthetics {

  //--------------------------------------------------------------------------
  // public:
  //--------------------------------------------------------------------------
  PassiveBlock::PassiveBlock(Core *core, Scene *scene) {
  }

  PassiveBlock::~PassiveBlock() {
  }

  int PassiveBlock::noOfFaces() {
    return 0;
  }

  Vector3 PassiveBlock::getOrientation(int face) {
    return Vector3(0, 0, 0);
  }

  void PassiveBlock::addUnit(int face, Unit *unit) {
  }

  Unit *PassiveBlock::getUnit(int face) {
    return NULL;
  }

  void PassiveBlock::handleEvent(Event *event) {
  }
}

extern "C" {
  static int passiveBlockFactory(lua_State *L) {
    lua_getfield(L, LUA_REGISTRYINDEX, "factory");
    void *p = lua_touserdata(L, 1);
    lua_pop(L, 1);
    fprintf(stderr, "PassiveBlock factory call: %p:%p\n", L, p);
    return 0;
  }

  static const struct luaL_Reg passiveBlockFuncs[] = {
    { "factory", passiveBlockFactory },
    { NULL, NULL }
  };

  int luaopen_libPassiveBlock(lua_State *L) {
    passiveBlockFactory(L);
    luaL_register(L, "passive.block", passiveBlockFuncs);
    return 1;
  }
}
