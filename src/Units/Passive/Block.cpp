//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "UnitFactory.hpp"
#include "UnitPlugging.hpp"
#include "Units/Passive/Block.hpp"

using namespace Polycode;
namespace Synthetics {
  namespace Units {
    namespace Passive {

      //--------------------------------------------------------------------------
      // Unit interface
      //--------------------------------------------------------------------------
      Block::Block(Core *core, Polycode::CollisionScene *scene) {
        m_core = core;
        m_scene = scene;
        m_color = Color(0.3, 0.9, 0.3, 1.0);

        m_shape = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1,1,1);
        m_shape->colorAffectsChildren = false;
        m_shape->setColor(m_color.r, m_color.g, m_color.b, 0.4);
        m_shape->setPosition(0.0, 0.0, 0.0);
        m_shape->setUserData(this);
        m_shape->alphaTest = true;

        m_plugging = NULL;
      }

      Block::~Block() {
        m_scene->removeEntity(m_shape);
        delete m_shape;
        if (m_plugging) {
          delete m_plugging;
        }
      }

      void Block::init() {
        m_plugging = new UnitPlugging(m_scene, this, 6);
        m_plugging->addOrientation(0, Vector3(0, 0, -1));
        m_plugging->addOrientation(1, Vector3(-1, 0, 0));
        m_plugging->addOrientation(2, Vector3(0, 0, 1));
        m_plugging->addOrientation(3, Vector3(1, 0, 0));
        m_plugging->addOrientation(4, Vector3(0, 1, 0));
        m_plugging->addOrientation(5, Vector3(0, -1, 0));
      }

      UnitPlugging *Block::getPlugging() {
        return m_plugging;
      }

      void Block::setActive(bool on) {
        m_plugging->setActive(on);
        if (on) {
          m_shape->setColor(m_color);
        }
        else {
          m_shape->setColor(m_color.r, m_color.g, m_color.b, 0.4);
        }
      }


      void Block::handleEvent(Unit::Event *event) {
      }

      Polycode::ScenePrimitive * Block::getPolycodeObject() {
        return m_shape;
      }

      //----------------------------------------------------------------------
      // Unit factory
      //----------------------------------------------------------------------
      PolycodeUnit *BlockCreator(Polycode::Core *core, Polycode::CollisionScene *scene) {
        PolycodeUnit *unit = new Block(core, scene);
        unit->init();
        return unit;
      }

      static int BlockRegister(lua_State *L) {
        lua_getfield(L, LUA_REGISTRYINDEX, "factory");
        UnitFactory *factory = (UnitFactory *)lua_touserdata(L, 1);
        lua_pop(L, 1);
        factory->addCreator("Passive.Block", &BlockCreator);
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
