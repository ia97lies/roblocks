//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Components/Factory.hpp"
#include "CommandAdd.hpp"

namespace Synthetics {
  namespace Constructor {
    CommandAdd::CommandAdd(Robot *robot, Component *component, Polycode::Core *core, Polycode::Scene *scene) {
      m_robot = robot;
      m_component = component;
      m_name = component->getName();
      m_core = core;
      m_scene = scene;
      m_activePlug = robot->getActivePlug();
    }

    CommandAdd::~CommandAdd() {}

    void CommandAdd::execute() {
      m_robot->add();
    }

    void CommandAdd::undo() {
      Plug *plug = m_component->getPart(0)->getPlug(0);
      m_robot->activate(plug->getShape());
      m_robot->remove();
      m_component = Components::Factory::get()->createComponent(m_name, m_core, m_scene);
      m_robot->place(m_component);
      m_robot->activate(m_activePlug->getShape());
    }
  }
}


