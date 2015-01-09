//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE LoadCompounds
#include <boost/test/unit_test.hpp>
#include "Part.hpp"

using namespace Polycode;
using namespace Synthetics;

class MyPart : public Part {
  public:
    MyPart() {}
    ~MyPart() {}
    Polycode::Entity *getShape() { return NULL; }
};

class MyKnob : public Knob {
  public:
    MyKnob() {}
    ~MyKnob() {}
    Polycode::Entity *getShape() { return NULL; }
    void handleInput(Polycode::Vector3 value) { }
};

BOOST_AUTO_TEST_CASE(test_part_instantiate) {
  MyPart part();
}

BOOST_AUTO_TEST_CASE(test_part_default_values) {
  MyPart *part = new MyPart();

  BOOST_CHECK(part->getNoPlugs() == 0);
  BOOST_CHECK_THROW(part->getPlug(0), std::out_of_range);
  BOOST_CHECK(part->getPlug((Entity *)NULL) == NULL);
  BOOST_CHECK(part->getShape() == NULL);
}

BOOST_AUTO_TEST_CASE(test_part_add_plug) {
  MyPart *part = new MyPart();
  Plug *plug = new Plug(Vector3(0,0,0), Vector3(0,0,0));

  part->addPlug(plug);
  BOOST_CHECK(part->getNoPlugs() == 1);
  BOOST_CHECK(part->getPlug(0) == plug);
}

BOOST_AUTO_TEST_CASE(test_part_add_many_plugs) {
  MyPart *part = new MyPart();
  Plug *plug1 = new Plug(Vector3(0,0,0), Vector3(0,0,0));
  Plug *plug2 = new Plug(Vector3(0,0,0), Vector3(0,0,0));
  Plug *plug3 = new Plug(Vector3(0,0,0), Vector3(0,0,0));

  part->addPlug(plug1);
  part->addPlug(plug2);
  part->addPlug(plug3);

  BOOST_CHECK(part->getNoPlugs() == 3);
  BOOST_CHECK(part->getPlug(0) == plug1);
  BOOST_CHECK(part->getPlug(1) == plug2);
  BOOST_CHECK(part->getPlug(2) == plug3);
}

BOOST_AUTO_TEST_CASE(test_part_add_plug_get_by_shape) {
  MyPart *part = new MyPart();
  Plug *plug = new Plug(Vector3(0,0,0), Vector3(0,0,0));

  part->addPlug(plug);
  BOOST_CHECK(part->getPlug(plug->getShape()) == plug);
}

BOOST_AUTO_TEST_CASE(test_part_add_plug_get_plug_found) {
  MyPart *part = new MyPart();
  Plug *plug = new Plug(Vector3(0,0,0), Vector3(0,0,0));
  Plug *plug2 = new Plug(Vector3(0,0,0), Vector3(0,0,0));

  part->addPlug(plug);
  BOOST_CHECK(part->getPlug(plug2->getShape()) == NULL);
}

BOOST_AUTO_TEST_CASE(test_part_add_many_plug_get_many_and_get_one_not_found) {
  MyPart *part = new MyPart();
  Plug *plug1 = new Plug(Vector3(0,0,0), Vector3(0,0,0));
  Plug *plug2 = new Plug(Vector3(0,0,0), Vector3(0,0,0));
  Plug *plug3 = new Plug(Vector3(0,0,0), Vector3(0,0,0));
  Plug *plugNotAdded = new Plug(Vector3(0,0,0), Vector3(0,0,0));

  part->addPlug(plug1);
  part->addPlug(plug2);
  part->addPlug(plug3);
  BOOST_CHECK(part->getPlug(plug1->getShape()) == plug1);
  BOOST_CHECK(part->getPlug(plug2->getShape()) == plug2);
  BOOST_CHECK(part->getPlug(plug3->getShape()) == plug3);
  BOOST_CHECK(part->getPlug(plugNotAdded->getShape()) == NULL);
}

BOOST_AUTO_TEST_CASE(test_part_set_get_knob) {
  MyKnob *knob = new MyKnob();
  MyPart *part = new MyPart();
  part->setKnob(knob);
  BOOST_CHECK(part->getKnob() == knob);
}
