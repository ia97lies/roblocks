//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "BlockFactory.hpp"
#include "BlockPlugging.hpp"
#include "Blocks/Actor/Servo.hpp"

using namespace Polycode;
namespace Synthetics {
  namespace Blocks {
    namespace Actor {

      //--------------------------------------------------------------------------
      // Block interface
      //--------------------------------------------------------------------------
      Servo::Servo(Polycode::CollisionScene *scene) {
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

      Servo::~Servo() {
        m_scene->removeEntity(m_shape);
        delete m_shape;
        if (m_plugging) {
          delete m_plugging;
        }
      }

      void Servo::init() {
        m_plugging = new BlockPlugging(m_scene, this, 6);
        m_plugging->addOrientation(0, Vector3(0, 0, -1));
        m_plugging->addOrientation(1, Vector3(-1, 0, 0));
        m_plugging->addOrientation(2, Vector3(0, 0, 1));
        m_plugging->addOrientation(3, Vector3(1, 0, 0));
        m_plugging->addOrientation(4, Vector3(0, 1, 0));
        m_plugging->addOrientation(5, Vector3(0, -1, 0));
      }

      BlockPlugging *Servo::getPlugging() {
        return m_plugging;
      }

      Polycode::ScenePrimitive * Servo::getShape() {
        return m_shape;
      }

      //----------------------------------------------------------------------
      // Block factory
      //----------------------------------------------------------------------
      Block *ServoCreator(Polycode::CollisionScene *scene) {
        Servo *hub = new Servo(scene);
        hub->init();
        return hub;
      }

      static int ServoRegister(lua_State *L) {
        lua_getfield(L, LUA_REGISTRYINDEX, "factory");
        BlockFactory *factory = (BlockFactory *)lua_touserdata(L, 1);
        lua_pop(L, 1);
        factory->addCreator("Actor.Servo", &ServoCreator);
        return 0;
      }

      static const struct luaL_Reg ServoFuncs[] = {
        { "register", ServoRegister },
        { NULL, NULL }
      };
    }
  }
}

//----------------------------------------------------------------------------
// Shared library hook
//----------------------------------------------------------------------------
extern "C" {
  int luaopen_libActorServo(lua_State *L) {
    luaL_register(L, "Actor.Servo", Synthetics::Blocks::Passive::ServoFuncs);
    return 1;
  }
}
