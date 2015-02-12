//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "PolyCamera.h"
#include "PolySound.h"
#include "PolySceneSound.h"
#include "PolyScenePrimitive.h"
#include "ValueRangeMapping.hpp"
#include "Plug.hpp"
#include "Components/Factory.hpp"
#include "Components/Active/Loudspeaker.hpp"

#define __MY_NAME "Active.Loudspeaker"

using namespace Polycode;
namespace Synthetics {
  namespace Components {
    namespace Active {

      class Body : public ::Synthetics::Part {
        public:
          Body() {
            m_entity = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1,1,1);
            m_entity->setMaterialByName("LoudspeakerMaterial");
            m_color = Color(0.7, 0.7, 0.7, 1.0);
            m_entity->colorAffectsChildren = false;
            m_entity->setColor(m_color);
            m_entity->setPosition(0, 0, 0);
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

      class SoundKnob : public Knob {
        public:
          SoundKnob(Part *body, SceneSound *sound) {
            m_sound = sound;
            m_entity = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.4,1.25,0.4);
            m_entity->setColor(0.0, 1.0, 0.0, 0.5);
            body->getShape()->addChild(m_entity);
            m_entity->setPosition(0, 0, 0);
            m_curValue = Vector3(2,0,0);
          }

          virtual ~SoundKnob() {
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
            m_sound->getSound()->setVolume(mapping.map().x);
          }

        private:
          SceneSound *m_sound;
          Vector3 m_curValue;
          Polycode::Entity *m_entity;
      };

      //--------------------------------------------------------------------------
      // Components interface
      //--------------------------------------------------------------------------
      Loudspeaker::Loudspeaker(Polycode::Scene *scene) {
        fprintf(stderr, "Create Loudspeaker\n");
        m_scene = scene;
        m_body = new Body();
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

        m_sound = new SceneSound("Resources/test.wav", 20, 50, false);
        m_sound->getSound()->Play(true);
        m_sound->getSound()->setVolume(0);
        m_sound->getSound()->setSoundDirection(Vector3(1,0,0));
        m_body->getShape()->addChild(m_sound);

        m_knob = new SoundKnob(m_body, m_sound);
        m_body->setKnob(m_knob);
      }

      Loudspeaker::~Loudspeaker() {
        fprintf(stderr, "Destroy Loudspeaker\n");
        delete m_knob;
        delete m_sound;
        delete m_body;
      }
      
      std::string Loudspeaker::getName() {
        return __MY_NAME;
      }

      int Loudspeaker::getNoParts() {
        return 1;
      }

      Part *Loudspeaker::getPart(int i) {
        if (i == 0) {
          return m_body;
        }
        return NULL;
      }

      void Loudspeaker::enable(bool on) {
          m_body->getShape()->enabled = on;
      }

      void Loudspeaker::send() {
      }

      void Loudspeaker::update(Polycode::Vector3 delta) {
      }

      //----------------------------------------------------------------------
      // Components factory
      //----------------------------------------------------------------------
      Component *LoudspeakerCreator(Polycode::Core *core, Polycode::Scene *scene) {
        Loudspeaker *loudspeaker = new Loudspeaker(scene);
        return loudspeaker;
      }

      static int LoudspeakerRegister(lua_State *L) {
        lua_getfield(L, LUA_REGISTRYINDEX, "factory");
        Components::Factory *factory = (Components::Factory *)lua_touserdata(L, 1);
        lua_pop(L, 1);
        factory->addCreator(__MY_NAME, &LoudspeakerCreator);
        return 0;
      }

      static const struct luaL_Reg LoudspeakerFuncs[] = {
        { "register", LoudspeakerRegister },
        { NULL, NULL }
      };
    }
  }
}

//----------------------------------------------------------------------------
// Shared library hook
//----------------------------------------------------------------------------
extern "C" {
  int luaopen_libActiveLoudspeaker(lua_State *L) {
    luaL_register(L, __MY_NAME, Synthetics::Components::Active::LoudspeakerFuncs);
    return 1;
  }
}
