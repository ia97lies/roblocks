//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "PolyCamera.h"
#include "PolySceneLight.h"
#include "PolyScenePrimitive.h"
#include "ValueRangeMapping.hpp"
#include "Plug.hpp"
#include "Components/Factory.hpp"
#include "Components/Active/Light.hpp"

#define __MY_NAME "Active.Light"

using namespace Polycode;
namespace Synthetics {
  namespace Components {
    namespace Active {

      class Body : public ::Synthetics::Part {
        public:
          Body(SceneLight *light) {
            m_light = light;
            m_entity = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.8,0.8,0.8);
            m_entity->setMaterialByName("ComponentMaterial");
            m_color = Color(0.7, 0.7, 0.7, 1.0);
            m_entity->colorAffectsChildren = false;
            m_entity->setColor(m_color);
            m_entity->setPosition(0, 0, 0);
            Vector3 pos[5];
            Vector3 form[5];
            pos[0] = Vector3(0.0, 0.0, 0.4);
            form[0] = Vector3(1,1,0.2);
            pos[1] = Vector3(0.0, 0.0, -0.4);
            form[1] = Vector3(1,1,0.2);
            pos[2] = Vector3(0.0, 0.4, 0.0);
            form[2] = Vector3(1,0.2,1);
            pos[3] = Vector3(0.0, -0.4, 0.0);
            form[3] = Vector3(1,0.2,1);
            pos[4] = Vector3(-0.4, 0.0, 0.0);
            form[4] = Vector3(0.2,1,1);
            for (int i = 0; i < 5; i++) {
              wall[i] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, form[i].x, form[i].y, form[i].z);
              wall[i]->setPosition(pos[i]);
              wall[i]->setMaterialByName("ComponentMaterial");
              wall[i]->colorAffectsChildren = false;
              wall[i]->setColor(m_color);
              m_entity->addChild(wall[i]);
            }
          }
          virtual ~Body() {
            for (int i = 0; i < 5; i++) {
              delete wall[i];
            }
            delete m_entity;
          }

          Polycode::Entity *getShape() {
            return m_entity;
          }

          void update(Polycode::Vector3 input) {
            ValueRangeMapping mapping(0, 30, input);
            m_light->setIntensity(mapping.map().x);
          }

        private:
          Polycode::ScenePrimitive *m_entity;
          Polycode::Color m_color;
          ScenePrimitive *wall[5];
          SceneLight *m_light;
      };

      class LightKnob : public Knob {
        public:
          LightKnob(Body *body) {
            m_body = body;
            m_entity = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.4,1.25,0.4);
            m_entity->setColor(0.0, 1.0, 0.0, 0.5);
            m_body->getShape()->addChild(m_entity);
            m_entity->setPosition(0, 0, 0);
            m_curValue = Vector3(0,0,0);
          }

          virtual ~LightKnob() {
          }
          
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
            m_body->update(m_curValue);
          }

        private:
          Vector3 m_curValue;
          Body *m_body;
          Polycode::Entity *m_entity;
      };

      //--------------------------------------------------------------------------
      // Components interface
      //--------------------------------------------------------------------------
      Light::Light(Polycode::Scene *scene) {
        fprintf(stderr, "Create Light\n");
        m_scene = scene;

        m_light = new SceneLight(SceneLight::POINT_LIGHT, m_scene, 1);
        m_light->setPosition(0.8,0,0);
        m_light->setLightColor(1,1,1);
        m_light->setIntensity(0);
        m_scene->addLight(m_light);

        m_body = new Body(m_light);
        Plug *plug = new Plug(Vector3(0,0,-1.0), Vector3(0,-90,0));
        plug->setInput(true);
        plug->setParent(this);
        m_body->addPlug(plug);
        plug = new Plug(Vector3(-1.0,0,0), Vector3(0,0,0));
        plug->setParent(this);
        m_body->addPlug(plug);
        plug = new Plug(Vector3(0,0,1.0), Vector3(0,-270,0));
        plug->setParent(this);
        m_body->addPlug(plug);
        plug = new Plug(Vector3(0,1.0,0), Vector3(0,0,90));
        plug->setParent(this);
        m_body->addPlug(plug);
        plug = new Plug(Vector3(0,-1.0,0), Vector3(0,0,270));
        plug->setParent(this);
        m_body->addPlug(plug);
        m_body->getShape()->addChild(m_light);

        m_knob = new LightKnob(dynamic_cast<Body *>(m_body));
        m_body->setKnob(m_knob);
      }

      Light::~Light() {
        fprintf(stderr, "Destroy Light\n");
        m_scene->removeLight(m_light);
        m_body->getShape()->removeChild(m_light);
        // This is done by Part, not sure if that is a good idea
        // but Part as well delete all Plugs
        //delete m_knob;
        delete m_light;
        delete m_body;
      }
      
      std::string Light::getName() {
        return __MY_NAME;
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

      void Light::updateNg() {
        Component::updateNg();
        Body *body = dynamic_cast<Body *>(m_body);
        body->update(getOutput());
      }

      //----------------------------------------------------------------------
      // Components factory
      //----------------------------------------------------------------------
      Component *LightCreator(Polycode::Core *core, Polycode::Scene *scene) {
        Light *light = new Light(scene);
        return light;
      }

      static int LightRegister(lua_State *L) {
        lua_getfield(L, LUA_REGISTRYINDEX, "factory");
        Components::Factory *factory = (Components::Factory *)lua_touserdata(L, 1);
        lua_pop(L, 1);
        factory->addCreator(__MY_NAME, &LightCreator);
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
    luaL_register(L, __MY_NAME, Synthetics::Components::Active::LightFuncs);
    return 1;
  }
}
