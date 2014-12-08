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
      Block::Block(Core *core, Polycode::CollisionScene *scene) {
        fprintf(stderr, "Create a passive block\n");
        m_faces[0] = Vector3(0, 0, -1);
        m_faces[1] = Vector3(-1, 0, 0);
        m_faces[2] = Vector3(0, 0, 1);
        m_faces[3] = Vector3(1, 0, 0);
        m_faces[4] = Vector3(0, 1, 0);
        m_faces[5] = Vector3(0, -1, 0);

        m_shapeColor = Vector3(0.3, 0.9, 0.3);
        m_markerColor = Vector3(0.8, 0.2, 0.2);

        m_activeFace = 0;
        for (int i = 0; i < this->noFaces(); i++) {
          m_childs[i] = NULL;
        }

        m_core = core;
        m_scene = scene;

        m_shape = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1,1,1);
        m_shape->colorAffectsChildren = false;
        m_shape->setColor(m_shapeColor.x, m_shapeColor.y, m_shapeColor.z, 0.4);
        m_shape->setPosition(0.0, 0.0, 0.0);
        m_shape->setUserData(this);
        m_shape->alphaTest = true;

        for (int i = 0 ; i < this->noFaces(); i++) {
          m_connectors[i] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.5,0.5,0.5);
          m_shape->addChild(m_connectors[i]);
          m_connectors[i]->setColor(m_shapeColor.x, m_shapeColor.y, m_shapeColor.z, 0.6);
          m_connectors[i]->setPosition(this->getOrientation(i) * 0.4);
        }

        this->setActiveFace(0);
      }

      Block::~Block() {
        fprintf(stderr, "Destroy a passive block\n");
        for (int i = 0; i < this->noFaces(); i++) {
          if (m_childs[i] != NULL) {
            m_childs[i]->removeUnit(this);
          }
        }
        m_scene->removeEntity(m_shape);
        delete m_shape;
        for (int i = 0; i < this->noFaces(); i++) {
          delete m_connectors[i];
        }
      }

      int Block::noFaces() {
        return s_noFaces;
      }

      bool Block::addUnit(Unit *unit) {
        bool ok = true;
        if (m_childs[m_activeFace] == NULL) {
          m_childs[m_activeFace] = unit;
          unit->linkUnit(this);
          ScenePrimitive *shape = unit->getPolycodeObject();
          ScenePrimitive *selectedShape = this->getPolycodeObject();
          selectedShape->addChild(shape);
          m_scene->trackCollision(shape);
          shape->setPosition(this->getOrientation(m_activeFace));

          Vector3 o1 = this->getOrientation(m_activeFace);
          Vector3 o2 = unit->getOrientation(unit->getActiveFace());
          float angle = acos(o1.dot(o2)) + PI;
          angle = angle < 2*PI ? angle : 0;
          Vector3 axis = o1.crossProduct(o2);
          if (axis.length() == 0) {
            if (o2.x == 0) {
              axis.x = 1;
            }
            else if (o2.y == 0) {
              axis.y = 1;
            }
            else {
              axis.z = 1;
            }
          } 
          Vector3 rotation = axis * (angle * (-1) * 180 / PI);
          fprintf(stderr, "x: %f, y:%f, z: %f\n", rotation.x, rotation.y, rotation.z);
          shape->setRotationEuler(rotation);
        }
        else {
          ok = false;
        }
        return ok;
      }
 
      void Block::linkUnit(Unit *unit) {
        m_childs[m_activeFace] = unit;
      }

      void Block::removeUnit(Unit *unit) {
        for (int face = 0; face < s_noFaces; face++) {
          if (m_childs[face] == unit) {
            m_shape->removeChild(unit->getPolycodeObject());
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
        if (face >= 0 && face < s_noFaces) {
          m_connectors[m_activeFace]->setColor(m_shapeColor.x, m_shapeColor.y, m_shapeColor.z, 0.4);
          m_activeFace = face;
          m_connectors[m_activeFace]->setColor(m_markerColor.x, m_markerColor.y, m_markerColor.z, 1.0);
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
      Unit *BlockCreator(Polycode::Core *core, Polycode::CollisionScene *scene) {
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
