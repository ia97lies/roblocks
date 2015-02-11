//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "PolyScenePrimitive.h"
#include "ValueRangeMapping.hpp"
#include "Plug.hpp"
#include "Components/Factory.hpp"
#include "Components/Passive/Wedge.hpp"

#define __MY_NAME "Passive.Wedge"

using namespace Polycode;
namespace Synthetics {
  namespace Components {
    namespace Passive {

      class Body : public ::Synthetics::Part {
        public:
          Body() {
            m_entity = new ScenePrimitive(ScenePrimitive::TYPE_CYLINDER, 1,0.5,20);
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
      Wedge::Wedge() {
        fprintf(stderr, "Create Wedge\n");
        m_input = Vector3(0,0,0);
        m_output = Vector3(0,0,0);
        m_body = new Body();
        Plug *plug = new Plug(Vector3(1,0,1), Vector3(0,-45,0));
        m_body->addPlug(plug);
        plug = new Plug(Vector3(-std:sqrt(2),0,1), Vector3(0,45,0));
        m_body->addPlug(plug);
        plug = new Plug(Vector3(0,0,-1), Vector3(0,90,0));
        m_body->addPlug(plug);
      }

      Wedge::~Wedge() {
        fprintf(stderr, "Destroy Wedge\n");
        delete m_body;
      }

      std::string Wedge::getName() {
        return __MY_NAME;
      }

      int Wedge::getNoParts() {
        return 1;
      }

      Part *Wedge::getPart(int i) {
        if (i == 0) {
          return m_body;
        }
        return NULL;
      }

      void Wedge::enable(bool on) {
        m_body->getShape()->enabled = on;
      }

      void Wedge::send() {
        for (int i = 0; i < getNoEntries(); i++) {
          Component *component = dynamic_cast<Component *>(get(i));
          component->update(m_output);
        }
        m_output = m_input;
      }

      void Wedge::update(Polycode::Vector3 input) {
        ValueRangeMapping mapping(0, 100, input);
        m_input = mapping.value();
      }

      //----------------------------------------------------------------------
      // Components factory
      //----------------------------------------------------------------------
      Component *WedgeCreator(Polycode::Core *core, Polycode::Scene *scene) {
        Wedge *hub = new Wedge();
        return hub;
      }

      static int WedgeRegister(lua_State *L) {
        lua_getfield(L, LUA_REGISTRYINDEX, "factory");
        Components::Factory *factory = (Components::Factory *)lua_touserdata(L, 1);
        lua_pop(L, 1);
        factory->addCreator(__MY_NAME, &WedgeCreator);
        return 0;
      }

      static const struct luaL_Reg WedgeFuncs[] = {
        { "register", WedgeRegister },
        { NULL, NULL }
      };
    }
  }
}

//----------------------------------------------------------------------------
// Shared library hook
//----------------------------------------------------------------------------
extern "C" {
  int luaopen_libPassiveWedge(lua_State *L) {
    luaL_register(L, __MY_NAME, Synthetics::Components::Passive::WedgeFuncs);
    return 1;
  }
}
