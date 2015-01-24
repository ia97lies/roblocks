//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------
//
#define BOOST_TEST_MODULE TestCompounds
#include <boost/test/unit_test.hpp>
#include "Compound.hpp"

using namespace Synthetics;

class Mock : public Compound {
  public:
    Mock() { 
      m_visit = false; 
    }
    
    virtual ~Mock() {}

    virtual std::string getName() {
      return "Compound::Mock";
    }

    void visit() {
      m_visit = true;
    }

    bool hasBeenVisited() {
      return m_visit;
    }

    void reset() {
      m_visit = false;
    }

  private:
    bool m_visit;
};

class DoForAll : public IterateMethod {
  public:
    DoForAll() {}
    ~DoForAll() {}
    virtual void call(Compound *parent, Compound *compound) {
      Mock *mock = dynamic_cast<Mock *>(compound);
      if (mock) {
        mock->visit();
      }
    }
};

BOOST_AUTO_TEST_CASE(test_compound_get_default_name) {
  Compound *compound = new Compound();
  BOOST_CHECK(compound->getName() == "<none>");
}

BOOST_AUTO_TEST_CASE(test_compound_get_name) {
  Compound *compound = new Mock();
  BOOST_CHECK(compound->getName() == "Compound::Mock");
}

BOOST_AUTO_TEST_CASE(test_compound_add_one) {
  Mock *mock = new Mock();
  Compound *compound = new Compound();
  
  compound->add(mock);
  BOOST_CHECK(compound->getNoEntries() == 1);
  BOOST_CHECK(compound->get(0) == mock);
}

BOOST_AUTO_TEST_CASE(test_compound_add_manny) {
  Mock *mock = new Mock();
  Compound *compound = new Compound();
  
  compound->add(mock);
  compound->add(mock);
  compound->add(mock);
  BOOST_CHECK(compound->getNoEntries() == 3);
  BOOST_CHECK(compound->get(0) == mock);
  BOOST_CHECK(compound->get(1) == mock);
  BOOST_CHECK(compound->get(2) == mock);
}

BOOST_AUTO_TEST_CASE(test_compound_add_one_remove_one) {
  Mock *mock = new Mock();
  Compound *compound = new Compound();
  
  compound->add(mock);
  BOOST_CHECK(compound->getNoEntries() == 1);
  BOOST_CHECK(compound->get(0) == mock);
  compound->remove(0);
  BOOST_CHECK(compound->getNoEntries() == 0);
  BOOST_CHECK_THROW(compound->get(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_compound_add_many_remove_one_add_one) {
  Mock *mock = new Mock();
  Compound *compound = new Compound();
  
  compound->add(mock);
  compound->add(mock);
  compound->add(mock);
  BOOST_CHECK(compound->getNoEntries() == 3);
  compound->remove(1);
  BOOST_CHECK(compound->getNoEntries() == 2);
  BOOST_CHECK(compound->get(0) == mock);
  BOOST_CHECK(compound->get(1) == mock);
  BOOST_CHECK_THROW(compound->get(2), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_compound_add_many_replace_one) {
  Mock *mock = new Mock();
  Mock *mock2 = new Mock();
  Compound *compound = new Compound();
  
  compound->add(mock);
  compound->add(mock);
  compound->add(mock);
  BOOST_CHECK(compound->getNoEntries() == 3);
  compound->add(1, mock2);
  BOOST_CHECK(compound->getNoEntries() == 3);
  BOOST_CHECK(compound->get(0) == mock);
  BOOST_CHECK(compound->get(1) == mock2);
  BOOST_CHECK(compound->get(2) == mock);
}

BOOST_AUTO_TEST_CASE(test_compound_add_many_remove_two_size_change) {
  Mock *mock = new Mock();
  Compound *compound = new Compound();
  
  compound->add(mock);
  compound->add(mock);
  compound->add(mock);
  BOOST_CHECK(compound->size() == 3);
  compound->remove(0);
  BOOST_CHECK(compound->size() == 2);
  compound->remove(1);
  BOOST_CHECK(compound->size() == 1);
}

BOOST_AUTO_TEST_CASE(test_compound_do_for_all_one_element) {
  Mock *mock = new Mock();
  Compound *compound = new Compound();
  
  compound->add(mock);
  BOOST_CHECK(!mock->hasBeenVisited());

  compound->iterate(new DoForAll());
  BOOST_CHECK(mock->hasBeenVisited());
}

BOOST_AUTO_TEST_CASE(test_compound_do_for_all_more_elements) {
  Compound *compound = new Compound();
  Mock *mock[10];
  for (int i = 0; i < 10; i++) {
    mock[i] = new Mock();
    compound->add(mock[i]);
  }

  for (int i = 0; i < 10; i++) {
    BOOST_CHECK(!mock[i]->hasBeenVisited());
  }

  compound->iterate(new DoForAll());

  for (int i = 0; i < 10; i++) {
    BOOST_CHECK(mock[i]->hasBeenVisited());
  }
}

BOOST_AUTO_TEST_CASE(test_compound_do_for_all_more_elements_more_levels) {
  Compound *compound = new Compound();
  Mock *mock[10];
  Mock *mock2[10][10];
  for (int i = 0; i < 10; i++) {
    mock[i] = new Mock();
    compound->add(mock[i]);
    for (int j = 0; j < 10; j++) {
      mock2[i][j] = new Mock();
      mock[i]->add(mock2[i][j]);
    }
  }

  for (int i = 0; i < 10; i++) {
    BOOST_CHECK(!mock[i]->hasBeenVisited());
    for (int j = 0; j < 10; j++) {
      BOOST_CHECK(!mock2[i][j]->hasBeenVisited());
    }
  }

  compound->iterate(new DoForAll());

  for (int i = 0; i < 10; i++) {
    BOOST_CHECK(mock[i]->hasBeenVisited());
    for (int j = 0; j < 10; j++) {
      BOOST_CHECK(mock2[i][j]->hasBeenVisited());
    }
  }
}

BOOST_AUTO_TEST_CASE(test_compound_do_for_all_point_to_myself) {
  Mock *mock = new Mock();
  mock->add(mock);
  mock->iterate(new DoForAll());
  BOOST_CHECK(mock->hasBeenVisited());
}

BOOST_AUTO_TEST_CASE(test_compound_do_for_all_cycled_compounds) {
  Mock *mock = new Mock();
  Mock *mock2 = new Mock();
  mock->add(mock2);
  mock2->add(mock);
  mock->iterate(new DoForAll());
  BOOST_CHECK(mock->hasBeenVisited());
  BOOST_CHECK(mock2->hasBeenVisited());
}

BOOST_AUTO_TEST_CASE(test_compound_do_for_all_tree_cycled_compounds) {
  Mock *mock = new Mock();
  Mock *mock2 = new Mock();
  Mock *mock3 = new Mock();
  mock->add(mock2);
  mock2->add(mock3);
  mock3->add(mock);
  mock->iterate(new DoForAll());
  BOOST_CHECK(mock->hasBeenVisited());
  BOOST_CHECK(mock2->hasBeenVisited());
  BOOST_CHECK(mock3->hasBeenVisited());
}

BOOST_AUTO_TEST_CASE(test_compound_do_for_all_with_all_connected_compounds) {
  Mock *mock[4];
  for (int i = 0; i < 4; i++) {
    mock[i] = new Mock();
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      mock[i]->add(mock[j]);
    }
  }
  mock[0]->iterate(new DoForAll());

  for (int i = 0; i < 4; i++) {
    BOOST_CHECK(mock[i]->hasBeenVisited());
  }
}

BOOST_AUTO_TEST_CASE(test_compound_do_for_all_twice_for_one_element) {
  Mock *mock = new Mock();
  Compound *compound = new Compound();
  
  compound->add(mock);

  for (int i = 0; i < 10; i++) {
    BOOST_CHECK(!mock->hasBeenVisited());
    compound->iterate(new DoForAll());
    BOOST_CHECK(mock->hasBeenVisited());
    mock->reset();
  }
}

BOOST_AUTO_TEST_CASE(test_compound_do_for_all_twice_for_two_chained_element) {
  Mock *mock = new Mock();
  Mock *mock2 = new Mock();
  Compound *compound = new Compound();
  
  compound->add(mock);
  mock->add(mock2);

  for (int i = 0; i < 10; i++) {
    BOOST_CHECK(!mock->hasBeenVisited());
    BOOST_CHECK(!mock2->hasBeenVisited());
    compound->iterate(new DoForAll());
    BOOST_CHECK(mock->hasBeenVisited());
    BOOST_CHECK(mock2->hasBeenVisited());
    mock->reset();
    mock2->reset();
  }
}

BOOST_AUTO_TEST_CASE(test_compound_do_for_all_twice_for_three_cycled_element) {
  Mock *mock = new Mock();
  Mock *mock2 = new Mock();
  Mock *mock3 = new Mock();
  
  mock->add(mock2);
  mock2->add(mock3);
  mock3->add(mock);

  for (int i = 0; i < 10; i++) {
    BOOST_CHECK(!mock->hasBeenVisited());
    BOOST_CHECK(!mock2->hasBeenVisited());
    BOOST_CHECK(!mock3->hasBeenVisited());
    mock->iterate(new DoForAll());
    BOOST_CHECK(mock->hasBeenVisited());
    BOOST_CHECK(mock2->hasBeenVisited());
    BOOST_CHECK(mock3->hasBeenVisited());
    mock->reset();
    mock2->reset();
    mock3->reset();
  }
}

BOOST_AUTO_TEST_CASE(test_compound_get_parents_of_a_given_compound) {
  Compound *compound = new Compound();
  Compound *compound2 = new Compound();
  
  compound->add(compound2);

  std::vector<Compound *> parents = compound->getParents(compound2);
  BOOST_CHECK(parents.size() == 1);
  BOOST_CHECK(parents.at(0) == compound);
}

BOOST_AUTO_TEST_CASE(test_compound_get_parents_of_a_given_compound_cirrcular_reference) {
  Compound *compound = new Compound();
  
  compound->add(compound);

  std::vector<Compound *> parents = compound->getParents(compound);
  BOOST_CHECK(parents.size() == 1);
  BOOST_CHECK(parents.at(0) == compound);
}

BOOST_AUTO_TEST_CASE(test_compound_get_parents_of_a_given_compound_multiple_parents) {
  Compound *compound = new Compound();
  Compound *compound2 = new Compound();
  Compound *compound3 = new Compound();
  Compound *compound4 = new Compound();
  
  compound->add(compound2);
  compound->add(compound3);
  compound->add(compound4);
  compound3->add(compound2);
  compound4->add(compound2);

  std::vector<Compound *> parents = compound->getParents(compound2);
  BOOST_CHECK(parents.size() == 3);
}

BOOST_AUTO_TEST_CASE(test_compound_add_one_remove_one_by_reference) {
  Mock *mock = new Mock();
  Compound *compound = new Compound();
  
  compound->add(mock);
  BOOST_CHECK(compound->getNoEntries() == 1);
  BOOST_CHECK(compound->get(0) == mock);
  compound->remove(mock);
  BOOST_CHECK(compound->getNoEntries() == 0);
  BOOST_CHECK_THROW(compound->get(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_compound_get_tag_without_initial_set_tag) {
  Compound compound;

  BOOST_CHECK(compound.getTag() == NULL);
}

BOOST_AUTO_TEST_CASE(test_compound_set_get_tag) {
  Tag tag;
  Compound compound;

  compound.setTag(&tag);
  BOOST_CHECK(compound.getTag() == &tag);
}

