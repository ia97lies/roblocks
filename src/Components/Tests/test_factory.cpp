//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestFactory
#include <vector>
#include <boost/test/unit_test.hpp>
#include "PolyScene.h"
#include "Components/Factory.hpp"

using namespace Synthetics;

BOOST_AUTO_TEST_CASE(test_get_instantiate) {
  Components::Factory *factory = Components::Factory::get();
  BOOST_CHECK(factory != NULL);

  Components::Factory *factory2 = Components::Factory::get();
  BOOST_CHECK(factory == factory2);
}

Component *MockCreator(Polycode::PhysicsScene *scene) {
  return (Component *)1;
}

BOOST_AUTO_TEST_CASE(test_add_create_func_get_create_func) {
  Components::Factory *factory = Components::Factory::get();
  BOOST_CHECK(factory != NULL);

  factory->addCreator("My.Super.Mock", MockCreator);
  Component *test = factory->createComponent("My.Super.Mock", NULL);
  BOOST_CHECK(test == (Component *)1);
  test = factory->createComponent("Do.Not.Exist", NULL);
  BOOST_CHECK(test == NULL);
}

BOOST_AUTO_TEST_CASE(test_add_many_create_func_get_names) {
  Components::Factory *factory = Components::Factory::get();
  BOOST_CHECK(factory != NULL);

  factory->addCreator("My.Super.Mock", MockCreator);
  factory->addCreator("My.Super.Mock.two", MockCreator);
  factory->addCreator("My.Super.Mock.three", MockCreator);

  std::vector<std::string> names = factory->getNames();
  BOOST_CHECK(names.size() == 3);
  BOOST_CHECK(names[0] == "My.Super.Mock");
  BOOST_CHECK(names[1] == "My.Super.Mock.two");
  BOOST_CHECK(names[2] == "My.Super.Mock.three");
}

