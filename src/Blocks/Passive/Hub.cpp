//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "BlockFactory.hpp"
#include "BlockPlugging.hpp"
#include "Blocks/Passive/Hub.hpp"

using namespace Polycode;
namespace Synthetics {
  namespace Blocks {
    namespace Passive {

      //--------------------------------------------------------------------------
      // Block interface
      //--------------------------------------------------------------------------
      Hub::Hub(Polycode::CollisionScene *scene) {
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

      Hub::~Hub() {
        m_scene->removeEntity(m_shape);
        delete m_shape;
        if (m_plugging) {
          delete m_plugging;
        }
      }

      void Hub::init() {
        m_plugging = new BlockPlugging(m_scene, this, 6);
        m_plugging->addOrientation(0, Vector3(0, 0, -1));
        m_plugging->addOrientation(1, Vector3(-1, 0, 0));
        m_plugging->addOrientation(2, Vector3(0, 0, 1));
        m_plugging->addOrientation(3, Vector3(1, 0, 0));
        m_plugging->addOrientation(4, Vector3(0, 1, 0));
        m_plugging->addOrientation(5, Vector3(0, -1, 0));
      }

      BlockPlugging *Hub::getPlugging() {
        return m_plugging;
      }

      void Hub::handleEvent(Unit::Event *event) {
      }

      Polycode::ScenePrimitive * Hub::getPolycodeObject() {
        return m_shape;
      }

      //----------------------------------------------------------------------
      // Block factory
      //----------------------------------------------------------------------
      Block *HubCreator(Polycode::CollisionScene *scene) {
        Hub *hub = new Hub(scene);
        hub->init();
        return hub;
      }

      static int HubRegister(lua_State *L) {
        lua_getfield(L, LUA_REGISTRYINDEX, "factory");
        BlockFactory *factory = (BlockFactory *)lua_touserdata(L, 1);
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
    luaL_register(L, "Passive.Hub", Synthetics::Blocks::Passive::HubFuncs);
    return 1;
  }
}
