//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Polycode.h"
#include "Components/Factory.hpp"
#include "CommandRemove.hpp"

namespace Synthetics {
  namespace Constructor {
    CommandRemove::CommandRemove(Robot *robot, Component *component, Polycode::Core *core, Polycode::Scene *scene) {
      m_robot = robot;
      m_name = component->getName();
      m_rotation = component->getPart(0)->getShape()->getRotationEuler();
      m_core = core;
      m_scene = scene;
    }

    CommandRemove::~CommandRemove() {}

    void CommandRemove::execute() {
      Components::Factory *factory = Components::Factory::get();
      m_robot->remove();
    }

    void CommandRemove::undo() {
      Component *component = Components::Factory::get()->createComponent(m_name, m_core, m_scene);
      component->getPart(0)->getShape()->setRotationEuler(m_rotation);
      m_robot->place(component);
      m_robot->add();
    }
  }
}


