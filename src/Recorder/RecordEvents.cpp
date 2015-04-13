//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolyLogger.h"
#include "RecordEvents.hpp"

using namespace Polycode;

namespace Synthetics {
  namespace Recorder {

    RecordEvents::RecordEvents(Core *core, Configurator *conf) {
      m_core = core;
      m_conf = conf;

      activate(m_conf->getRecord());
      if (m_on) {
        m_file = fopen("record.bin", "w");
      }
      memset(&m_event, 0, sizeof(m_event));
    }

    RecordEvents::~RecordEvents() {}

    void RecordEvents::handleEvent(Polycode::Event *e) {
      if(e->getDispatcher() == m_core->getInput()) {
        InputEvent *inputEvent = (InputEvent*)e;
        memset(&m_event, 0, sizeof(m_event));
        m_event.event = e->getEventCode();
        m_event.ticks = m_core->getTicks();
        switch(e->getEventCode()) {
          case InputEvent::EVENT_KEYDOWN:
            {
              m_event.key = inputEvent->keyCode();
              m_event.charCode = inputEvent->getCharCode();
            }
            break;
          case InputEvent::EVENT_MOUSEWHEEL_UP:
          case InputEvent::EVENT_MOUSEWHEEL_DOWN:
          case InputEvent::EVENT_MOUSEDOWN:
          case InputEvent::EVENT_MOUSEUP:
            {
              m_event.mouseButton = inputEvent->getMouseButton();
            }
            break;
          case InputEvent::EVENT_MOUSEMOVE:
            {
              m_event.x = (int )inputEvent->getMousePosition().x;
              m_event.y = (int )inputEvent->getMousePosition().y;
            }
            break;
        }
      }
    }

    void RecordEvents::update(Number dt) {
      if (m_on && m_event.event != 0) {
        m_event.dt = dt;
        for (int i = 0; i < sizeof(m_event); i++) {
          fputc(((char *)&m_event)[i], m_file);
        }
        fflush(NULL);
        m_event.event = 0;
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
