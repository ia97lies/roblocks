//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "PolyScenePrimitive.h"
#include "ValueRangeMapping.hpp"
#include "Plug.hpp"
#include "Components/Factory.hpp"
#include "Components/Active/Servo.hpp"

#define __MY_NAME "Active.Servo"

using namespace Polycode;
namespace Synthetics {
  namespace Components {
    namespace Active {

      class Body : public ::Synthetics::Part {
        public:
          Body() {
            m_entity = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.2,1,1);
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

      class Link : public ::Synthetics::Part {
        public:
          Link() {
            m_entity = new ScenePrimitive(ScenePrimitive::TYPE_CYLINDER, 1,0.5,20);
            m_entity->setMaterialByName("ComponentMaterial");
            m_color = Color(0.7, 0.7, 0.7, 1.0);
            m_entity->colorAffectsChildren = false;
            m_entity->setColor(m_color);
            m_entity->setPosition(0.0, 0.0, 0.0);
          }
          virtual ~Link() {}

          void rotate(Polycode::Vector3 rotate) {
            m_entity->setRotationEuler(rotate);
          }

          void update(Polycode::Vector3 input) {
            ValueRangeMapping mapping(90, -90, input);
            Polycode::Vector3 rotation(0, mapping.map().x, 0);
            rotate(rotation);
          }

          Polycode::Entity *getShape() {
            return m_entity;
          }

        private:
          Polycode::ScenePrimitive *m_entity;
          Polycode::Color m_color;
      };

      class ServoKnob : public Knob {
        public:
          ServoKnob(Link *link) {
            m_link = link;
            m_entity = new ScenePrimitive(ScenePrimitive::TYPE_CYLINDER, 1.2,0.4,20);
            m_entity->setColor(0.0, 1.0, 0.0, 0.5);
            m_link->getShape()->addChild(m_entity);
            m_curValue = Vector3(0, 0, 0);
          }

          virtual ~ServoKnob() {}
          
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
            ValueRangeMapping mapping(0, 1, m_curValue + delta);
            m_curValue = mapping.value();
            m_link->update(m_curValue);
          }

        private:
          Vector3 m_curValue;
          Link *m_link;
          Polycode::Entity *m_entity;
      };

      //--------------------------------------------------------------------------
      // Components interface
      //--------------------------------------------------------------------------
      Servo::Servo() {
        fprintf(stderr, "Create Servo\n");
        m_output = Vector3(0,0,0);
        m_body[0] = new Body();
        Plug *plug = new Plug(Vector3(-0.2,0,0), Vector3(0,0,0));
        plug->setInput(true);
        plug->setParent(this);
        m_body[0]->addPlug(plug);

        Link *link = new Link();
        m_body[1] = link;
        m_body[1]->getShape()->setPosition(0.6,0,0);
        m_body[1]->getShape()->setRotationEuler(Vector3(0,90,0));
        ServoKnob *servoKnob = new ServoKnob(link);
        link->setKnob(servoKnob);

        m_body[2] = new Body();
        m_body[2]->getShape()->setPosition(0.6,0,0);
        plug = new Plug(Vector3(0.2,0,0), Vector3(0,0,0));
        plug->setParent(this);
        m_body[2]->addPlug(plug);

        // TODO: add a hinge joint 
        // m_hingeJoint(m_body[1], m_body[2], Vector3(0,0,0), Vector3(-1,0,0), Vector3(0,1,0), Vector3(0,1,0))
      }

      Servo::~Servo() {
        fprintf(stderr, "Destroy Servo\n");
        for (int i = 0; i < 3; i++) {
          delete m_body[i];
        }
      }

      std::string Servo::getName() {
        return __MY_NAME;
      }

      // TODO:
      // Joint *Servo::getJoint() {
      //   return m_hingeJoint;
      // }

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

      void Servo::update(Polycode::Vector3 input) {
        Link *link = dynamic_cast<Link *>(m_body[1]);
        link->update(input);
        m_input = input;
      }

      //----------------------------------------------------------------------
      // Components factory
      //----------------------------------------------------------------------
      Component *ServoCreator(Polycode::Core *core, Polycode::Scene *scene) {
        Servo *hub = new Servo();
        return hub;
      }

      static int ServoRegister(lua_State *L) {
        lua_getfield(L, LUA_REGISTRYINDEX, "factory");
        Components::Factory *factory = (Components::Factory *)lua_touserdata(L, 1);
        lua_pop(L, 1);
        factory->addCreator(__MY_NAME, &ServoCreator);
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
  int luaopen_libActiveServo(lua_State *L) {
    luaL_register(L, __MY_NAME, Synthetics::Components::Active::ServoFuncs);
    return 1;
  }
}
