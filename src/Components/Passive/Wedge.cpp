//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include <math.h>
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
            m_entity = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.2,0.5,0.5);
            m_entity->setMaterialByName("ComponentMaterial");
            m_color = Color(0.4, 0.4, 0.7, 0.0);
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

      class Link : public ::Synthetics::Part {
        public:
          Link() {
            m_entity = new ScenePrimitive(ScenePrimitive::TYPE_CYLINDER, 1,0.5,20);
            m_entity->setMaterialByName("ComponentMaterial");
            m_color = Color(0.7, 0.7, 0.7, 1.0);
            m_entity->colorAffectsChildren = false;
            m_entity->setColor(m_color);
            m_entity->setPosition(0, 0, 0);
            m_entity->setRotationEuler(Vector3(0, 60, 0));
          }
          virtual ~Link() {}

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

        m_body[0] = new Body();
        Plug *plug = new Plug(Vector3(-1,0,0), Vector3(0,0,0));
        plug->setParent(this);
        plug->setInOut(true);
        m_body[0]->addPlug(plug);

        Link *link = new Link();
        m_body[1] = link;
        m_body[1]->getShape()->setPosition(0,0,0);

        m_body[2] = new Body();
        m_body[2]->getShape()->setPosition(0,0,0);
        plug = new Plug(Vector3(1,0,0), Vector3(0,0,0));
        plug->setParent(this);
        plug->setInOut(true);
        m_body[2]->addPlug(plug);

      }

      Wedge::~Wedge() {
        fprintf(stderr, "Destroy Wedge\n");
        for (int i = 0; i < 3; i++) {
          delete m_body[i];
        }
      }

      std::string Wedge::getName() {
        return __MY_NAME;
      }

      int Wedge::getNoParts() {
        return 3;
      }

      Part *Wedge::getPart(int i) {
        if (i >= 0 || i < getNoParts()) {
          return m_body[i];
        }
        return NULL;
      }

      void Wedge::enable(bool on) {
        for (int i = 0; i < getNoParts(); i++) {
          m_body[i]->getShape()->enabled = on;
        }
      }

      void Wedge::update(Plug *sendingPlug, Polycode::Vector3 input) {
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
