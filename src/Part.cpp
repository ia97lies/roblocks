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
  };

  Part::~Part() {
    for (int i = 0; i < m_plugs.size(); i++) {
      if (m_plugs.at(i)) {
        delete m_plugs.at(i);
      }
    }
    if (m_knob) {
      delete m_knob;
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

  // TODO: Part::plug(Part *part, float factor)
  //       Need to get my active plug, do nothing when no active plug
  void Part::plug(Plug *plug1, Plug *plug2, float factor) {
      Vector3 pos1 = plug1->getPosition();
      Vector3 pos2 = plug2->getPosition();
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

