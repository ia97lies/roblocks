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
        for (int i = 0; i < this->noFaces(); i++) {
          m_childs[i] = NULL;
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

      int Block::noFaces() {
        return s_noFaces;
      }

      bool Block::addUnit(int face, Unit *unit) {
        bool ok = true;
        if (face >= 0 && face < s_noFaces && m_childs[face] == NULL) {
          m_childs[face] = unit;
          unit->linkUnit(unit->getActiveFace(), this);
          ScenePrimitive *shape = unit->getPolycodeObject();
          ScenePrimitive *selectedShape = this->getPolycodeObject();
          shape->setPosition(selectedShape->getPosition() + this->getOrientation(face));

          // TODO: as well as rotate in a way that both faces do face each other
          Vector3 o1 = this->getOrientation(face);
          Vector3 o2 = unit->getOrientation(unit->getActiveFace());
          float angle = acos(o1.dot(o2)) + PI;
          angle = angle < 2*PI ? angle : 0;
          Vector3 axis = o1.crossProduct(o2);
          if (axis.length() == 0) {
            if (o2.x) {
              axis.x = 1;
            }
            else if (o2.y) {
              axis.y = 1;
            }
            else {
              axis.z = 1;
            }
          } 
          Vector3 rotation = axis * (angle * 180 / PI);
          fprintf(stderr, "x: %f, y:%f, z: %f\n", rotation.x, rotation.y, rotation.z);
          shape->setRotationEuler(rotation);

          // TODO: have to rotate the orientation vectors of the added unit as well!
          //       ==> add a rotate method, maybe protected
        }
        else {
          ok = false;
        }
        return ok;
      }
 
      void Block::linkUnit(int face, Unit *unit) {
        if (face >= 0 && face < s_noFaces && m_childs[face] == NULL) {
          m_childs[face] = unit;
        }
      }

      void Block::removeUnit(Unit *unit) {
        for (int face = 0; face < s_noFaces; face++) {
          if (m_childs[face] == unit) {
            m_childs[face] = NULL;
          }
        }
      }

      Unit *Block::getUnit(int face) {
        Unit *child = NULL;
        if (face >= 0 && face < s_noFaces) {
          child = m_childs[face];
        }

        return child;
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
        if (face >= 0 && face < s_noFaces && m_childs[face] == NULL) {
          m_activeFace = face;
        }
        else {
          ok = false;
        }
        return ok;
      }

      int Block::getActiveFace() {
        return m_activeFace;
      }

      int Block::noChilds() {
        int no = 0;
        for (int face = 0; face < s_noFaces; face++) {
          no += m_childs[face] ? 1 : 0;
        }
        return no;
      }

      Vector3 Block::getOrientation(int face) {
        return m_faces[face];
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
