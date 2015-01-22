//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestSerializer
#include <boost/test/unit_test.hpp>
#include "Polycode.h"
#include "Component.hpp"

using namespace Synthetics;
using namespace Polycode;

class PartMock : public Part {
  public:
    PartMock() {
      m_shape = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 1, 1);
    }
    ~PartMock() {}
    Polycode::Entity *getShape() { return m_shape; }
  private:
    Polycode::Entity *m_shape;
};

class ComponentMock : public Component {
  public:
    ComponentMock() { 
      m_part[0] = new PartMock();
      m_plug[0] = new Plug(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_part[0]->addPlug(m_plug[0]);
      m_plug[3] = new Plug(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_part[0]->addPlug(m_plug[3]);

      m_part[1] = new PartMock();
      m_plug[1] = new Plug(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_part[1]->addPlug(m_plug[1]);
      m_plug[2] = new Plug(Vector3(0, 0, 0), Vector3(0, 0, 0));
      m_part[1]->addPlug(m_plug[2]);

    }
    virtual ~ComponentMock() {}

    virtual int getNoParts() { return 2; }
    virtual Part *getPart(int i) { return m_part[i]; }
    virtual void enable(bool on) {};
    Plug *getMyPlug(int i) { return m_plug[i]; }

  private:
    Part *m_part[2];
    Plug *m_plug[4];
};

BOOST_AUTO_TEST_CASE(test_serializer_instantiate) {
}

