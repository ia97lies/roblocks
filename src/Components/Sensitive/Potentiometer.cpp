//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "PolyScenePrimitive.h"
#include "ValueRangeMapping.hpp"
#include "Plug.hpp"
#include "Components/Factory.hpp"
#include "Components/Active/Servo.hpp"
#include "Components/Sensitive/Potentiometer.hpp"

#define __MY_NAME "Sensitive.Potentiometer"

using namespace Polycode;
namespace Synthetics {
  namespace Components {
    namespace Sensitive {

      //--------------------------------------------------------------------------
      // Custom shape definition
      //--------------------------------------------------------------------------
      class Body : public ::Synthetics::Part {
        public:
          Body() {
            m_entity = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1,1,1);
            m_entity->setMaterialByName("ComponentMaterial");
            m_color = Color(0.4, 1.0, 0.4, 1.0);
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

      class Shaft : public ::Synthetics::Part {
        public:
          Shaft() {
            m_entity = new ScenePrimitive(ScenePrimitive::TYPE_CYLINDER, 0.5,0.5,20);
            m_entity->setMaterialByName("PotentiometerMaterial");
            m_color = Color(0.3, 0.3, 0.3, 1.0);
            m_entity->colorAffectsChildren = false;
            m_entity->setColor(m_color);
            m_curValue = (0,0,0);
          }
          virtual ~Shaft() {}

          Vector3 getValue() {
            return m_curValue;
          }

          Polycode::Entity *getShape() {
            return m_entity;
          }

          void rotate(Polycode::Vector3 rotate) {
            m_entity->setRotationEuler(rotate);
          }

          void update(Polycode::Vector3 delta) {
            ValueRangeMapping mapping(0, 360, m_curValue + delta);
            m_curValue = mapping.value();
            Polycode::Vector3 rotation(0, mapping.map().x, 0);
            rotate(rotation);
          }

        private:
          Vector3 m_curValue;
          Polycode::ScenePrimitive *m_entity;
          Polycode::Color m_color;
      };

      class ShaftKnob : public Knob {
        public:
          ShaftKnob(Shaft *shaft) {
            m_shaft = shaft;
            m_entity = new ScenePrimitive(ScenePrimitive::TYPE_CYLINDER, 0.2, 0.4,20);
            m_entity->setColor(0.0, 1.0, 0.0, 0.5);
            m_entity->setPosition(0.0, 0.2, 0.0);
            m_shaft->getShape()->addChild(m_entity);
          }

          virtual ~ShaftKnob() {}
          
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
            m_shaft->update(delta);
          }

        private:
          Shaft *m_shaft;
          Polycode::Entity *m_entity;
      };

      //--------------------------------------------------------------------------
      // Components interface
      //--------------------------------------------------------------------------
      Potentiometer::Potentiometer() {
        fprintf(stderr, "Create Potentiometer\n");
        m_output = Vector3(0,0,0);
        m_body[0] = new Body();
        Plug *plug = new Plug(Vector3(1,0,0), Vector3(0,0,0));
        m_body[0]->addPlug(plug);
        plug = new Plug(Vector3(0,0,-1), Vector3(0,-90,0));
        m_body[0]->addPlug(plug);
        plug = new Plug(Vector3(-1,0,0), Vector3(0,0,0));
        m_body[0]->addPlug(plug);
        plug = new Plug(Vector3(0,0,1), Vector3(0,-270,0));
        m_body[0]->addPlug(plug);
        plug = new Plug(Vector3(0,-1,0), Vector3(0,0,270));
        m_body[0]->addPlug(plug);

        Shaft *shaft = new Shaft();
        m_body[1] = shaft;
        m_body[1]->getShape()->setPosition(0,0.75,0);
        ShaftKnob *knob = new ShaftKnob(shaft);
        m_body[1]->setKnob(knob);
      }

      Potentiometer::~Potentiometer() {
      }

      std::string Potentiometer::getName() {
        return __MY_NAME;
      }

      int Potentiometer::getNoParts() {
        return 2;
      }

      Part *Potentiometer::getPart(int i) {
        if (i >= 0 || i < 2) {
          return m_body[i];
        }
        return NULL;
      }

      void Potentiometer::enable(bool on) {
        for (int i = 0; i < 2; i++) {
          m_body[i]->getShape()->enabled = on;
        }
      }

      void Potentiometer::send() {
        Shaft *shaft = dynamic_cast<Shaft *>(m_body[1]);
        Vector3 delta = shaft->getValue() - m_output;
        for (int i = 0; i < getNoEntries(); i++) {
          Component *component = dynamic_cast<Component *>(get(i));
          component->update(delta);
        }
        m_output = shaft->getValue();
      }

      void Potentiometer::update(Polycode::Vector3 delta) {
        // nothing to do we are ourself a signal source
      }

      //----------------------------------------------------------------------
      // Components factory
      //----------------------------------------------------------------------
      Component *PotentiometerCreator(Polycode::Core *core, Polycode::Scene *scene) {
        Potentiometer *potentiometer = new Potentiometer();
        return potentiometer;
      }

      static int PotentiometerRegister(lua_State *L) {
        lua_getfield(L, LUA_REGISTRYINDEX, "factory");
        Components::Factory *factory = (Components::Factory *)lua_touserdata(L, 1);
        lua_pop(L, 1);
        factory->addCreator(__MY_NAME, &PotentiometerCreator);
        return 0;
      }

      static const struct luaL_Reg PotentiometerFuncs[] = {
        { "register", PotentiometerRegister },
        { NULL, NULL }
      };
    }
  }
}

//----------------------------------------------------------------------------
// Shared library hook
//----------------------------------------------------------------------------
extern "C" {
  int luaopen_libSensitivePotentiometer(lua_State *L) {
    luaL_register(L, __MY_NAME, Synthetics::Components::Sensitive::PotentiometerFuncs);
    return 1;
  }
}

