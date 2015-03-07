//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolyVector3.h"
#include "PolyEntity.h"
#include "Part.hpp"

using namespace Polycode;

namespace Synthetics {
  Part::Part() {
    m_knob = NULL;
    m_mass = 1.0;
  };

  Part::~Part() {
    for (int i = 0; i < getNoPlugs(); i++) {
      if (m_plugs.at(i)) {
        delete m_plugs.at(i);
      }
    }
    if (m_knob) {
      delete m_knob;
    }
  };

  void Part::setMass(float mass) {
    m_mass = mass;
  }

  float Part::getMass() {
    return m_mass;
  }

  int Part::getNoPlugs() {
    return m_plugs.size();
  }

  void Part::addPlug(Plug *plug) {
    m_plugs.push_back(plug);
  }

  Plug *Part::getPlug(int i) {
    return m_plugs.at(i);
  }

  Plug *Part::getPlug(Polycode::Entity *plugShape) {
    Plug *found = NULL;
    for (int i = 0; !found && i < getNoPlugs(); i++) {
      if (plugShape == m_plugs.at(i)->getShape()) {
        found = m_plugs.at(i);
      }
    }
    return found;
  }

  void Part::plug(Part *part, float factor) {
    Vector3 pos1 = 0;
    for (int i = 0; i < part->getNoPlugs(); i++) {
      if (part->getPlug(i)->isActive()) {
        pos1 = part->getPlug(i)->getPosition();
      }
    }
    Vector3 pos2 = 0;
    for (int i = 0; i < getNoPlugs(); i++) {
      if (m_plugs.at(i)->isActive()) {
        pos2 = m_plugs.at(i)->getPosition();
      }
    }
    float len = pos1.length() + pos2.length();
    pos1.Normalize();
    getShape()->setPosition(pos1 * len * factor);
  }

  void Part::setKnob(Knob *knob) {
    m_knob = knob;
  }

  Knob *Part::getKnob() {
    return m_knob;
  }
}

