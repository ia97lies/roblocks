//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "KeyLabel.hpp"

namespace Synthetics {
  namespace ShowKeyHits {

    KeyLabel::KeyLabel() : SceneLabel(" ", 18) {
      m_elapsed = 0;
      setColor(1,1,1,1);
      enabled = false;
    }

    KeyLabel::~KeyLabel() {
    }

    void KeyLabel::setLabel(std::string text) {
      setText(text);
      enabled = true;
    }

    void KeyLabel::update(Number dt) {
      if (enabled && m_elapsed < 2) {
        m_elapsed += dt;
        setColor(1,1,1, 1-(m_elapsed/2));
      }
      else if (enabled && m_elapsed > 2) {
        enabled = false;
        m_elapsed = 0;
      }
    }
  }
}

