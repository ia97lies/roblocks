//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "PolyScenePrimitive.h"
#include "ValueRangeMapping.hpp"
#include "Plug.hpp"
#include "Components/Factory.hpp"
#include "Components/Active/Linear.hpp"

#define __MY_NAME "Active.Linear"

using namespace Polycode;
namespace Synthetics {
  namespace Components {
    namespace Active {

      class Body : public ::Synthetics::Part {
        public:
          Body() {
            m_entity = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1,1,1);
            m_entity->setMaterialByName("ComponentMaterial");
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
          Polycode::ScenePrimitive *m_entity;
          Polycode::Color m_color;
      };

      class Rod : public ::Synthetics::Part {
        public:
          Rod() {
            m_entity = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.2,1,1);
            m_entity->setMaterialByName("ComponentMaterial");
            m_color = Color(0.7, 0.7, 0.7, 1.0);
            m_entity->colorAffectsChildren = false;
            m_entity->setColor(m_color);
            m_entity->setPosition(0.0, 0.0, 0.0);
          }
          virtual ~Rod() {
            delete m_entity;
          }

          Polycode::Entity *getShape() {
            return m_entity;
          }

        private:
          Polycode::ScenePrimitive *m_entity;
          Polycode::Color m_color;
      };

      class LinearKnob : public Knob {
        public:
          LinearKnob(Part *body, Part *rod) {
            m_rod = rod;
            m_entity = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.8,1.2,0.8);
            m_entity->setColor(0.0, 1.0, 0.0, 0.5);
            body->getShape()->addChild(m_entity);
            m_curValue = Vector3(0.5,0,0);
          }

          virtual ~LinearKnob() {}
          
          virtual void activate(bool on) {
            if (on) {
              m_entity->setColor(0.0, 1.0, 0.0, 1.0);
            }
            else {
              m_entity->setColor(0.0, 1.0, 0.0, 0.5);
            }
          }

          virtual Polycode::Entity *getShape() {
            return m_entity;
          } 

          virtual void handleInput(Polycode::Vector3 delta) {
            ValueRangeMapping mapping(Vector3(0, 0, 0), Vector3(1, 0, 0), m_curValue + delta);
            m_curValue = mapping.value();
            Vector3 pos(0.6, 0, 0);
            m_rod->getShape()->setPosition(mapping.map() + pos);
          }

        private:
          Part *m_rod;
          Vector3 m_curValue;
          Polycode::Entity *m_entity;
      };

      //--------------------------------------------------------------------------
      // Components interface
      //--------------------------------------------------------------------------
      Linear::Linear() {
        fprintf(stderr, "Create Linear\n");
        m_body[0] = new Body();
        Plug *plug = new Plug(Vector3(-1,0,0), Vector3(0,0,0));
        m_body[0]->addPlug(plug);

        m_body[1] = new Rod();
        m_body[1]->getShape()->setPosition(0.6,0,0);
        plug = new Plug(Vector3(0.2,0,0), Vector3(0,0,0));
        m_body[1]->addPlug(plug);

        LinearKnob *linearKnob = new LinearKnob(m_body[0], m_body[1]);
        m_body[0]->setKnob(linearKnob);

        // TODO: add a slider joint 
        // m_sliderJoint(m_body[1], m_body[2], Vector3(0,0,0), Vector3(-1,0,0), Vector3(0,1,0), Vector3(0,1,0))
      }

      Linear::~Linear() {
        fprintf(stderr, "Destroy Linear\n");
        for (int i = 0; i < 2; i++) {
          delete m_body[i];
        }
      }

      std::string Linear::getName() {
        return __MY_NAME;
      }

      // TODO:
      // Joint *Linear::getJoint() {
      //   return m_sliderJoint;
      // }

      int Linear::getNoParts() {
        return 2;
      }

      Part *Linear::getPart(int i) {
        if (i >= 0 || i < 2) {
          return m_body[i];
        }
        return NULL;
      }

      void Linear::enable(bool on) {
        for (int i = 0; i < 2; i++) {
          m_body[i]->getShape()->enabled = on;
        }
      }

      void Linear::update() {
      }

      //----------------------------------------------------------------------
      // Components factory
      //----------------------------------------------------------------------
      Component *LinearCreator(Polycode::Scene *scene) {
        Linear *hub = new Linear();
        return hub;
      }

      static int LinearRegister(lua_State *L) {
        lua_getfield(L, LUA_REGISTRYINDEX, "factory");
        Components::Factory *factory = (Components::Factory *)lua_touserdata(L, 1);
        lua_pop(L, 1);
        factory->addCreator(__MY_NAME, &LinearCreator);
        return 0;
      }

      static const struct luaL_Reg LinearFuncs[] = {
        { "register", LinearRegister },
        { NULL, NULL }
      };
    }
  }
}

//----------------------------------------------------------------------------
// Shared library hook
//----------------------------------------------------------------------------
extern "C" {
  int luaopen_libActiveLinear(lua_State *L) {
    luaL_register(L, __MY_NAME, Synthetics::Components::Active::LinearFuncs);
    return 1;
  }
}
