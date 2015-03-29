//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "PolyScenePrimitive.h"
#include "ValueRangeMapping.hpp"
#include "Plug.hpp"
#include "Components/Factory.hpp"
#include "Components/Passive/Hub.hpp"

#define __MY_NAME "Passive.Hub"

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
            setMass(0.5);
          }
          virtual ~Body() {
            delete m_entity;
          }

          virtual Polycode::Entity *getShape() {
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
        m_markerPlug = NULL;
        m_body = new Body();
        Plug *plug = new Plug(Vector3(1.0,0,0), Vector3(0,0,0));
        plug->setParent(this);
        plug->setInOut(true);
        m_body->addPlug(plug);
        plug = new Plug(Vector3(0,0,-1.0), Vector3(0,-90,0));
        plug->setParent(this);
        m_body->addPlug(plug);
        plug->setDeaf(true);
        plug = new Plug(Vector3(-1.0,0,0), Vector3(0,0,0));
        plug->setParent(this);
        m_body->addPlug(plug);
        plug->setInOut(true);
        plug = new Plug(Vector3(0,0,1.0), Vector3(0,-270,0));
        plug->setParent(this);
        m_body->addPlug(plug);
        plug->setInOut(true);
        plug = new Plug(Vector3(0,1.0,0), Vector3(0,0,90));
        plug->setParent(this);
        m_body->addPlug(plug);
        plug->setInOut(true);
        plug = new Plug(Vector3(0,-1.0,0), Vector3(0,0,270));
        plug->setParent(this);
        m_body->addPlug(plug);
        plug->setInOut(true);
      }

      Hub::~Hub() {
        fprintf(stderr, "Destroy Hub\n");
        delete m_body;
      }

      std::string Hub::getName() {
        return __MY_NAME;
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

      void Hub::shield() {
        for (int i = 0; i < m_body->getNoPlugs(); i++) {
          Plug *plug = m_body->getPlug(i);
          Plug *connectedPlug = m_body->getPlug(i)->getConnectedPlug();
          if (connectedPlug && (plug->isInput() || plug->isOutput())) {
            if (connectedPlug && connectedPlug->isInput() && !connectedPlug->isOutput()) {
              plug->setInput(false);
            }
            else if (connectedPlug && !connectedPlug->isInput() && connectedPlug->isOutput()) {
              plug->setInput(true);
            }
          }
        }
      }

      //----------------------------------------------------------------------
      // Components factory
      //----------------------------------------------------------------------
      Component *HubCreator(Polycode::PhysicsScene *scene) {
        Hub *hub = new Hub();
        return hub;
      }

      static int HubRegister(lua_State *L) {
        lua_getfield(L, LUA_REGISTRYINDEX, "factory");
        Components::Factory *factory = (Components::Factory *)lua_touserdata(L, 1);
        lua_pop(L, 1);
        factory->addCreator(__MY_NAME, &HubCreator);
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
    luaL_register(L, __MY_NAME, Synthetics::Components::Passive::HubFuncs);
    return 1;
  }
}
