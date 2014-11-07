#include <stdexcept>
#include "Synthetics/Hub.hpp"

namespace Synthetics {
  // ------------------------------------------------------------------------
  Hub::Hub() 
  {
    this->currentSideIndex = 0;
    this->maxSide = 6;
  }

  // ------------------------------------------------------------------------
  Hub::~Hub() 
  {
  }

  // ------------------------------------------------------------------------
  void Hub::connect(Object *object) 
  {
    this->connections[this->currentSideIndex];
    object->reference(this);
  }

  void Hub::reference(Object *object)
  {
    this->references[this->currentSideIndex];
  }

  // ------------------------------------------------------------------------
  void Hub::setSide(int side) 
  {
    if (side < this->maxSide) {
      this->currentSideIndex = side;
    }
    else {
      throw(new std::out_of_range("A hub only have 6 sides"));
    }
  }

  // ------------------------------------------------------------------------
  int Hub::getSide() 
  {
    return this->currentSideIndex;
  }

  // ------------------------------------------------------------------------
  void Hub::draw()
  {
  }
}

