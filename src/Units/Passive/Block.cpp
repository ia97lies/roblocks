//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "lua.hpp"
#include "UnitFactory.hpp"
#include "Units/Passive/Block.hpp"

using namespace Polycode;
namespace Synthetics {
  namespace Units {
    namespace Passive {

      //--------------------------------------------------------------------------
      // Unit interface
      //--------------------------------------------------------------------------
      Block::Block(Core *core, Scene *scene) {
        fprintf(stderr, "Create a passive block\n");
        m_faces[0] = Vector3(0, 0, -1);
        m_faces[1] = Vector3(-1, 0, 0);
        m_faces[2] = Vector3(0, 0, 1);
        m_faces[3] = Vector3(1, 0, 0);
        m_faces[4] = Vector3(0, 1, 0);
        m_faces[5] = Vector3(0, -1, 0);

        m_activeFace = 0;
        for (int i = 0; i < this->noOfFaces(); i++) {
          m_childs[i] = NULL;
          m_parents[i] = NULL;
        }

        m_core = core;
        m_scene = scene;

        m_shape = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1,1,1);
        m_shape->colorAffectsChildren = false;
        m_shape->setColor(0.3, 0.9, 0.3, 0.4);
        m_shape->setPosition(0.0, 0.0, 0.0);
        m_shape->setUserData(this);
      }

      Block::~Block() {
        fprintf(stderr, "Destroy a passive block\n");
        delete m_shape;
      }

      int Block::noOfFaces() {
        return s_noOfFaces;
      }

      Vector3 Block::getOrientation(int face) {
        return m_faces[face];
      }

      bool Block::addUnit(int face, Unit *unit) {
        bool ok = true;
        if (face >= 0 && face < s_noOfFaces && m_childs[face] == NULL) {
          m_childs[face] = unit;
          unit->setParent(this);
          ScenePrimitive *shape = unit->getPolycodeObject();
          ScenePrimitive *selectedShape = this->getPolycodeObject();
          shape->setPosition(selectedShape->getPosition() + this->getOrientation(face));
        }
        else {
          ok = false;
        }
        return ok;
      }

      Unit *Block::getUnit(int face) {
        if (face >= 0 && face < s_noOfFaces) {
          return m_childs[face];
        }

        return NULL;
      }

      void Block::setActive(bool on) {
        if (!on) {
          m_shape->setColor(0.3, 0.9, 0.3, 0.4);
        }
        else {
          m_shape->setColor(0.3, 0.9, 0.3, 1.0);
        }
      }

      bool Block::setActiveFace(int face) {
        bool ok = true;
        if (face >= 0 && face < s_noOfFaces && m_childs[face] == NULL) {
          m_activeFace = face;
        }
        else {
          ok = false;
        }
        return ok;
      }

      void Block::setParent(Unit *unit) {
        m_parents[m_activeFace] = unit;
      }

      bool Block::haveChilds() {
        bool have = false;
        for (int face = 0; face < s_noOfFaces; face++) {
          have |= m_childs[face] != NULL;
        }
        return have;
      }

      void Block::handleEvent(Event *event) {
      }

      Polycode::ScenePrimitive * Block::getPolycodeObject() {
        return m_shape;
      }

      //----------------------------------------------------------------------
      // Unit factory
      //----------------------------------------------------------------------
      Unit *BlockCreator(Polycode::Core *core, Polycode::Scene *scene) {
        return new Block(core, scene);
      }

      static int BlockRegister(lua_State *L) {
        lua_getfield(L, LUA_REGISTRYINDEX, "factory");
        UnitFactory *factory = (UnitFactory *)lua_touserdata(L, 1);
        lua_pop(L, 1);
        factory->addCreator("Passive.Block", &BlockCreator);
        return 0;
      }

      static const struct luaL_Reg BlockFuncs[] = {
        { "register", BlockRegister },
        { NULL, NULL }
      };
    }
  }
}

//----------------------------------------------------------------------------
// Shared library hook
//----------------------------------------------------------------------------
extern "C" {
  int luaopen_libPassiveBlock(lua_State *L) {
    luaL_register(L, "Passive.Block", Synthetics::Units::Passive::BlockFuncs);
    return 1;
  }
}
