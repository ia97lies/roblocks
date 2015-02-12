//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestPlug
#include <boost/test/unit_test.hpp>
#include "Plug.hpp"

using namespace Polycode;
using namespace Synthetics;

BOOST_AUTO_TEST_CASE(test_proper_initialization) {
  Plug plug(Vector3(0,0,0), Vector3(0,0,0));
  BOOST_CHECK(plug.getParent() == NULL);
  BOOST_CHECK(plug.getConnectedPlug() == NULL);
}

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

BOOST_AUTO_TEST_CASE(test_plug_set_get_remove_connected_plug) {
  Plug plug1(Vector3(1,0,0), Vector3(0,0,0));
  Plug plug2(Vector3(1,0,0), Vector3(0,0,0));
  plug1.setConnectedPlug(&plug2);
  
  BOOST_CHECK(plug1.getConnectedPlug() == &plug2);

  plug1.unsetConnectedPlug();
  BOOST_CHECK(plug1.getConnectedPlug() == NULL);
}

BOOST_AUTO_TEST_CASE(test_plug_set_get_parent) {
  Compound *compound = new Compound();
  Plug plug1(Vector3(1,0,0), Vector3(0,0,0));
  plug1.setParent(compound);
  
  BOOST_CHECK(plug1.getParent() == compound);
}

