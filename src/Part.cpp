//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolyEntity.h"
#include "Part.hpp"

namespace Synthetics {
  Part::Part() {
    m_knob = NULL;
  };

  Part::~Part() {
    for (int i = 0; i < m_plugs.size(); i++) {
      if (m_plugs.at(i)) {
        delete m_plugs.at(i);
      }
    }
  };

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
    for (int i = 0; !found && i < m_plugs.size(); i++) {
      if (plugShape == m_plugs.at(i)->getShape()) {
        found = m_plugs.at(i);
      }
    }
    return found;
  }

  void Part::setKnob(Knob *knob) {
    m_knob = knob;
  }

  Knob *Part::getKnob() {
    return m_knob;
  }
}

