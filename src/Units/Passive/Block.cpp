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
      // Unit interface
      //--------------------------------------------------------------------------
      Block::Block(Core *core, Scene *scene) {
        fprintf(stderr, "Create a passive block\n");
        m_faces[0] = Vector3(1, 0, 0);
        m_faces[1] = Vector3(-1, 0, 0);
        m_faces[2] = Vector3(0, 1, 0);
        m_faces[3] = Vector3(0, -1, 0);
        m_faces[4] = Vector3(0, 0, 1);
        m_faces[5] = Vector3(0, 0, -1);

        m_core = core;
        m_scene = scene;

        m_shape = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1,1,1);
        m_shape->setColor(0.0, 1.0, 1.0, 0.4);
        m_shape->setPosition(0.0, 0.0, 0.0);
      }

      Block::~Block() {
      }

      int Block::noOfFaces() {
        return 6;
      }

      Vector3 Block::getOrientation(int face) {
        return m_faces[face];
      }

      void Block::addUnit(int face, Unit *unit) {
      }

      Unit *Block::getUnit(int face) {
        return NULL;
      }

      void Block::handleEvent(Event *event) {
      }

      Polycode::ScenePrimitive * Block::getPolycodeObject() {
        return m_shape;
      }

      //----------------------------------------------------------------------
      // Unit factory
      //----------------------------------------------------------------------
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

//----------------------------------------------------------------------------
// Shared library hook
//----------------------------------------------------------------------------
extern "C" {
  int luaopen_libPassiveBlock(lua_State *L) {
    luaL_register(L, "Passive.Block", Synthetics::Units::Passive::BlockFuncs);
    return 1;
  }
}
