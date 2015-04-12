//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestKnob
#include <boost/test/unit_test.hpp>
#include "Polycode.h"
#include "Knob.hpp"

using namespace Polycode;
using namespace Synthetics;

class MyKnob : public Knob {
  public:
    MyKnob() {
      shape = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 1, 1);
      shape->setColor(getColor());
    }
    virtual ~MyKnob() {}
    virtual Entity *getShape() { return shape; }
    virtual void handleInput(Polycode::Vector3 delta) {}

    Entity *shape;
};

BOOST_AUTO_TEST_CASE(test_get_defined_color) {
  MyKnob knob;
  Color color = knob.getColor();
  BOOST_CHECK(Color(0.0,1.0,1.0,0.5) == color);
}

BOOST_AUTO_TEST_CASE(test_get_default_shape_color) {
  MyKnob knob;
  Color color = knob.getShape()->color;
  BOOST_CHECK(Color(0.0,1.0,1.0,0.5) == color);
}

BOOST_AUTO_TEST_CASE(test_knob_activate_off) {
  MyKnob knob;
  knob.activate(false);
  Color color = knob.getShape()->color;
  BOOST_CHECK(Color(0.0,1.0,1.0,0.5) == color);
}

BOOST_AUTO_TEST_CASE(test_knob_activate_on) {
  MyKnob knob;
  knob.activate(true);
  Color color = knob.getShape()->color;
  BOOST_CHECK(Color(0.0,1.0,1.0,1.0) == color);
}

