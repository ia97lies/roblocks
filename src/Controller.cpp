//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Controller.hpp"

namespace Synthetics {
  Controller::Controller() {}
  Controller::~Controller() {}

  void Controller::enter(Controller *controller) {
    m_parent = controller;
    activate();
    m_parent->deactivate();
  }

  void Controller::leave() {
    deactivate();
    m_parent->activate();
  }

}

