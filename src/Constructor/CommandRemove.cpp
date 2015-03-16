//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Polycode.h"
#include "Components/Factory.hpp"
#include "CommandRemove.hpp"

namespace Synthetics {
  namespace Constructor {
    CommandRemove::CommandRemove(Robot *robot, Polycode::Core *core, Polycode::Scene *scene) {
      m_robot = robot;
      Component *component = m_robot->getInPlace();
      m_isInPlace = true;
      if (!component) {
        component = m_robot->getActiveComponent();
        m_isInPlace = false;
      }
      if (component) {
        m_isNone = false;
        m_name = component->getName();
        m_rotation = component->getPart(0)->getShape()->getRotationEuler();
        // TODO: add a possibility to get active plug index
        m_core = core;
        m_scene = scene;
      }
      else {
        m_isNone = true;
      }
    }

    CommandRemove::~CommandRemove() {}

    void CommandRemove::execute() {
      if (!m_isNone) {
        m_robot->remove();
      }
    }

    void CommandRemove::undo() {
      if (!m_isNone) {
        Component *component = Components::Factory::get()->createComponent(m_name, m_core, m_scene);
        component->getPart(0)->getShape()->setRotationEuler(m_rotation);
        m_robot->place(component);
        if (!m_isInPlace) {
          m_robot->add();
        }
      }
    }
  }
}


