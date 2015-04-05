//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Components/Factory.hpp"
#include "CommandAdd.hpp"

namespace Synthetics {
  namespace Constructor {
    CommandAdd::CommandAdd(Robot *robot, Component *component) {
      m_robot = robot;
      m_component = component;
      m_activePlug = robot->getActivePlug();
    }

    CommandAdd::~CommandAdd() { }

    void CommandAdd::execute() {
      m_robot->add();
    }

    void CommandAdd::undo() {
      Plug *plug = m_component->getPart(0)->getPlug(0);
      m_robot->activate(plug->getShape());
      Polycode::Vector3 rotation = m_component->getPart(0)->getShape()->getRotationEuler();
      m_component = m_robot->remove();
      m_robot->place(m_component);
      m_robot->activate(m_activePlug->getShape());
      m_component->getPart(0)->getShape()->setRotationEuler(rotation);
    }
  }
}


