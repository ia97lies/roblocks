//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Components/Factory.hpp"
#include "CommandSetRoot.hpp"

namespace Synthetics {
  namespace Constructor {

    CommandSetRoot::CommandSetRoot(Robot *robot, Component *component, Polycode::Core *core, Polycode::Scene *scene) {
      m_robot = robot;
      m_component = component;
      m_name = component->getName();
      m_core = core;
      m_scene = scene;
    }

    CommandSetRoot::~CommandSetRoot() {}

    void CommandSetRoot::execute() {
      if (m_component == NULL) {
        m_component = Components::Factory::get()->createComponent(m_name, m_core, m_scene);
      }
      m_robot->setRoot(m_component);
    }

    void CommandSetRoot::undo() {
      // select one plug no mather which one
      Plug *plug = m_component->getPart(0)->getPlug(0);
      m_robot->activate(plug->getShape());
      m_robot->remove();
      m_component = NULL;
    }
  }
}

