//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "RecordEvents.hpp"

using namespace Polycode;

namespace Synthetics {
  namespace Recorder {

    RecordEvents::RecordEvents(Core *core, Configurator *conf) {
      m_core = core;
      m_conf = conf;

      activate(m_conf->getRecord());
    }

    RecordEvents::~RecordEvents() {}

    void RecordEvents::handleEvent(Polycode::Event *e) {
      if(e->getDispatcher() == m_core->getInput()) {
        InputEvent *inputEvent = (InputEvent*)e;
        m_eventCode = e->getEventCode();
        switch(e->getEventCode()) {
          case InputEvent::EVENT_KEYDOWN:
            {
              m_keyCode = inputEvent->keyCode();
              m_keyCharCode = inputEvent->getCharCode();
            }
            break;
          case InputEvent::EVENT_MOUSEWHEEL_UP:
          case InputEvent::EVENT_MOUSEWHEEL_DOWN:
          case InputEvent::EVENT_MOUSEDOWN:
          case InputEvent::EVENT_MOUSEUP:
            {
              m_mouseButton = inputEvent->getMouseButton();
            }
            break;
          case InputEvent::EVENT_MOUSEMOVE:
            {
              m_mousePosition = inputEvent->getMousePosition();
            }
            break;
        }
      }
    }

    void RecordEvents::update(Number dt) {
      if (m_on && m_eventCode != 0) {
        // write every frame
        fprintf(stderr, "%f;%d;%d;%d;%d;%d\n", dt, m_eventCode, m_keyCode, m_mouseButton, (int )m_mousePosition.x, (int )m_mousePosition.y);
        m_eventCode = 0;
        m_keyCode = 0;
        m_mouseButton = 0;
      }
    }

    void RecordEvents::activate(bool on) {
      m_on = on;
      if (m_on) {
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEUP);
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_UP);
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_DOWN);
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
      }
      else {
        m_core->getInput()->removeAllHandlersForListener(this);
      }
    }

  }
}
