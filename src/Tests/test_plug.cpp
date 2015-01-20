//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE LoadCompounds
#include <boost/test/unit_test.hpp>
#include "Plug.hpp"

using namespace Polycode;
using namespace Synthetics;

BOOST_AUTO_TEST_CASE(test_plug_getter) {
  Plug plug(Vector3(0,0,0), Vector3(0,0,0));
  
  BOOST_CHECK(plug.getPosition() == Vector3(0,0,0));
  BOOST_CHECK(plug.getRotation() == Vector3(0,0,0));
}

BOOST_AUTO_TEST_CASE(test_plug_getter_2) {
  Plug plug(Vector3(1,2,3), Vector3(4,5,6));
  
  BOOST_CHECK(plug.getPosition() == Vector3(1,2,3));
  BOOST_CHECK(plug.getRotation() == Vector3(4,5,6));
}

BOOST_AUTO_TEST_CASE(test_plug_face_to_face_rotation) {
  Plug plug1(Vector3(1,0,0), Vector3(0,0,0));
  Plug plug2(Vector3(1,0,0), Vector3(0,0,0));
  
  BOOST_CHECK(plug1.getFaceToFaceRotation(&plug2) == Vector3(0, -180, 0));
}

BOOST_AUTO_TEST_CASE(test_plug_face_to_face_rotation_2) {
  Plug plug1(Vector3(1,0,0), Vector3(0,0,0));
  Plug plug2(Vector3(-1,0,0), Vector3(0,0,0));
  
  BOOST_CHECK(plug1.getFaceToFaceRotation(&plug2) == Vector3(0, 0, 0));
}

BOOST_AUTO_TEST_CASE(test_plug_face_to_face_rotation_3) {
  Plug plug1(Vector3(1,0,0), Vector3(0,0,0));
  Plug plug2(Vector3(0,1,0), Vector3(0,0,0));
  
  BOOST_CHECK(plug1.getFaceToFaceRotation(&plug2) == Vector3(0, 0, -270));
}

BOOST_AUTO_TEST_CASE(test_plug_set_get_remove_compound) {
  Plug plug1(Vector3(1,0,0), Vector3(0,0,0));
  Compound *compound = new Compound();
  plug1.setCompound(compound);
  
  BOOST_CHECK(plug1.getCompound() == compound);

  plug1.unsetCompound();
  BOOST_CHECK(plug1.getCompound() == NULL);
}

