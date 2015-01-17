//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "PolyScenePrimitive.h"
#include "Plug.hpp"
#include "Components/Factory.hpp"
#include "Components/Passive/Hub.hpp"

using namespace Polycode;
namespace Synthetics {
  namespace Components {
    namespace Passive {

      class Body : public ::Synthetics::Part {
        public:
          Body() {
            m_entity = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1,1,1);
            m_entity->setMaterialByName("ComponentMaterial");
            m_color = Color(0.4, 0.4, 1.0, 1.0);
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
          Polycode::ScenePrimitive *m_entity;
          Polycode::Color m_color;
      };

      //--------------------------------------------------------------------------
      // Components interface
      //--------------------------------------------------------------------------
      Hub::Hub() {
        fprintf(stderr, "Create Hub\n");
        m_body = new Body();
        Plug *plug = new Plug(Vector3(1.0,0,0), Vector3(0,0,0));
        m_body->addPlug(plug);
        plug = new Plug(Vector3(0,0,-1.0), Vector3(0,-90,0));
        m_body->addPlug(plug);
        plug = new Plug(Vector3(-1.0,0,0), Vector3(0,0,0));
        m_body->addPlug(plug);
        plug = new Plug(Vector3(0,0,1.0), Vector3(0,-270,0));
        m_body->addPlug(plug);
        plug = new Plug(Vector3(0,1.0,0), Vector3(0,0,90));
        m_body->addPlug(plug);
        plug = new Plug(Vector3(0,-1.0,0), Vector3(0,0,270));
        m_body->addPlug(plug);
      }

      Hub::~Hub() {
        fprintf(stderr, "Destroy Hub\n");
        delete m_body;
      }

      int Hub::getNoParts() {
        return 1;
      }

      Part *Hub::getPart(int i) {
        if (i == 0) {
          return m_body;
        }
        return NULL;
      }

      void Hub::enable(bool on) {
        m_body->getShape()->enabled = on;
      }

      //----------------------------------------------------------------------
      // Components factory
      //----------------------------------------------------------------------
      Component *HubCreator(Polycode::Scene *scene) {
        Hub *hub = new Hub();
        return hub;
      }

      static int HubRegister(lua_State *L) {
        lua_getfield(L, LUA_REGISTRYINDEX, "factory");
        Components::Factory *factory = (Components::Factory *)lua_touserdata(L, 1);
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
    luaL_register(L, "Passive.Hub", Synthetics::Components::Passive::HubFuncs);
    return 1;
  }
}
