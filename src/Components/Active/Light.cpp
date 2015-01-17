//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "PolyCamera.h"
#include "PolySceneLight.h"
#include "PolyScenePrimitive.h"
#include "Plug.hpp"
#include "Components/Factory.hpp"
#include "Components/Active/Light.hpp"

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

      class LightKnob : public Knob {
        public:
          LightKnob(Part *body, Part *rod) {
            m_rod = rod;
            m_entity = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.8,1.2,0.8);
            m_entity->setColor(0.0, 1.0, 0.0, 0.5);
            body->getShape()->addChild(m_entity);
            m_curValue = Vector3(0.5,0,0);
          }

          virtual ~LightKnob() {}
          
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
            m_curValue += delta;
            if (m_curValue.x > 100) m_curValue.x = 100;
            if (m_curValue.x < 0) m_curValue.x = 0;
            Vector3 pos = Vector3(0.6, 0, 0);
            pos.x += m_curValue.x;
          }

        private:
          Part *m_rod;
          Vector3 m_curValue;
          Polycode::Entity *m_entity;
      };

      //--------------------------------------------------------------------------
      // Components interface
      //--------------------------------------------------------------------------
      Light::Light(Polycode::Scene *scene) {
        fprintf(stderr, "Create Light\n");
        m_body = new Body();
        Plug *plug = new Plug(Vector3(0,0,-1.0), Vector3(0,-90,0));
        m_body->addPlug(plug);
        plug = new Plug(Vector3(-1.0,0,0), Vector3(0,0,0));
        m_body->addPlug(plug);
        plug = new Plug(Vector3(0,0,1.0), Vector3(0,-270,0));
        m_body->addPlug(plug);
        plug = new Plug(Vector3(0,1.0,0), Vector3(0,0,90));
        m_body->addPlug(plug);
        plug = new Plug(Vector3(0,-1.0,0), Vector3(0,0,270));
        m_body->addPlug(plug);

        SceneLight *light = new SceneLight(SceneLight::SPOT_LIGHT, scene, 5);
        light->setPosition(1.2,0,0);
        light->setLightColor(1,1,1);
        scene->addLight(light);
        m_body->getShape()->addChild(light);
        light->lookAt(Vector3(1,0,0));
        light->enableShadows(true);
        light->getSpotlightCamera()->frustumCulling = false;
      }

      Light::~Light() {
        fprintf(stderr, "Destroy Light\n");
        delete m_body;
      }

      int Light::getNoParts() {
        return 1;
      }

      Part *Light::getPart(int i) {
        if (i == 0) {
          return m_body;
        }
        return NULL;
      }

      void Light::enable(bool on) {
          m_body->getShape()->enabled = on;
      }

      //----------------------------------------------------------------------
      // Components factory
      //----------------------------------------------------------------------
      Component *LightCreator(Polycode::Scene *scene) {
        Light *light = new Light(scene);
        return light;
      }

      static int LightRegister(lua_State *L) {
        lua_getfield(L, LUA_REGISTRYINDEX, "factory");
        Components::Factory *factory = (Components::Factory *)lua_touserdata(L, 1);
        lua_pop(L, 1);
        factory->addCreator("Active.Light", &LightCreator);
        return 0;
      }

      static const struct luaL_Reg LightFuncs[] = {
        { "register", LightRegister },
        { NULL, NULL }
      };
    }
  }
}

//----------------------------------------------------------------------------
// Shared library hook
//----------------------------------------------------------------------------
extern "C" {
  int luaopen_libActiveLight(lua_State *L) {
    luaL_register(L, "Active.Light", Synthetics::Components::Active::LightFuncs);
    return 1;
  }
}
