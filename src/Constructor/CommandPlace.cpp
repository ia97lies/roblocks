//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Components/Factory.hpp"
#include "CommandPlace.hpp"

namespace Synthetics {
  namespace Constructor {
    CommandPlace::CommandPlace(Robot *robot, Component *component, Polycode::Core *core, Polycode::Scene *scene) {
      m_robot = robot;
      m_component = component;
      m_name = component->getName();
      m_core = core;
      m_scene = scene;
    }

    CommandPlace::~CommandPlace() {}

    void CommandPlace::execute() {
      if (m_component == NULL) {
        m_component = Components::Factory::get()->createComponent(m_name, m_core, m_scene);
      }
      m_robot->place(m_component);
    }

    void CommandPlace::undo() {
      m_robot->remove();
      m_component = NULL;
    }
  }
}


