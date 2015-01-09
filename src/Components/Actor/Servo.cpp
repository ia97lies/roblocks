//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "PolyScenePrimitive.h"
#include "Plug.hpp"
#include "Components/Factory.hpp"
#include "Components/Actor/Servo.hpp"

using namespace Polycode;
namespace Synthetics {
  namespace Components {
    namespace Actor {

      class Body : public ::Synthetics::Part {
        public:
          Body() {
            m_entity = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1,1,1);
            m_color = Color(0.7, 0.7, 0.7, 1.0);
            m_entity->colorAffectsChildren = false;
            m_entity->setColor(m_color);
            m_entity->setPosition(0.0, 0.0, 0.0);
          }
          virtual ~Body() {
            delete m_entity;
          }

          Polycode::Entity *getShape() {
            return m_entity;
          }

        private:
          Polycode::Entity *m_entity;
          Polycode::Color m_color;
      };

      class Link : public ::Synthetics::Part {
        public:
          Link() {
            m_entity = new ScenePrimitive(ScenePrimitive::TYPE_CYLINDER, 1,0.6,20);
            m_color = Color(0.7, 0.7, 0.7, 1.0);
            m_entity->colorAffectsChildren = false;
            m_entity->setColor(m_color);
            m_entity->setPosition(0.0, 0.0, 0.0);
          }
          virtual ~Link() {}

          Polycode::Entity *getShape() {
            return m_entity;
          }

        private:
          Polycode::Entity *m_entity;
          Polycode::Color m_color;
      };

      //--------------------------------------------------------------------------
      // Components interface
      //--------------------------------------------------------------------------
      Servo::Servo() {
        fprintf(stderr, "Create Servo\n");
        m_body[0] = new Body();
        Plug *plug = new Plug(Vector3(-1.0,0,0), Vector3(0,0,0));
        m_body[0]->addPlug(plug);
        plug = new Plug(Vector3(0,1.0,0), Vector3(0,0,90));
        m_body[0]->addPlug(plug);
        plug = new Plug(Vector3(0,-1.0,0), Vector3(0,0,270));
        m_body[0]->addPlug(plug);

        m_body[1] = new Link();
        m_body[1]->getShape()->setPosition(1,0,0);
        m_body[1]->getShape()->setRotationEuler(Vector3(0,90,0));

        m_body[2] = new Body();
        m_body[2]->getShape()->setPosition(1,0,0);
        plug = new Plug(Vector3(1.0,0,0), Vector3(0,0,0));
        m_body[2]->addPlug(plug);
        plug = new Plug(Vector3(0,1.0,0), Vector3(0,0,90));
        m_body[2]->addPlug(plug);
        plug = new Plug(Vector3(0,-1.0,0), Vector3(0,0,270));
        m_body[2]->addPlug(plug);

      }

      Servo::~Servo() {
        fprintf(stderr, "Destroy Servo\n");
        for (int i = 0; i < 3; i++) {
          delete m_body[i];
        }
      }

      int Servo::getNoParts() {
        return 3;
      }

      Part *Servo::getPart(int i) {
        if (i >= 0 || i < 3) {
          return m_body[i];
        }
        return NULL;
      }

      void Servo::enable(bool on) {
        for (int i = 0; i < 3; i++) {
          m_body[i]->getShape()->enabled = on;
        }
      }

      //----------------------------------------------------------------------
      // Components factory
      //----------------------------------------------------------------------
      Component *ServoCreator() {
        Servo *hub = new Servo();
        return hub;
      }

      static int ServoRegister(lua_State *L) {
        lua_getfield(L, LUA_REGISTRYINDEX, "factory");
        Components::Factory *factory = (Components::Factory *)lua_touserdata(L, 1);
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
    luaL_register(L, "Actor.Servo", Synthetics::Components::Actor::ServoFuncs);
    return 1;
  }
}
