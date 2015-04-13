//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "Polycode.h"
#include "Event.hpp"
#include "PlayEvents.hpp"

using namespace Polycode;

namespace Synthetics {
  namespace Recorder {
    PlayEvents::PlayEvents(Polycode::Core *core, Configurator *conf) {
      m_core = core;
      m_conf = conf;

      if (m_conf->getPlay()) {
        m_file = fopen("record.bin", "r");
      }
    }

    PlayEvents::~PlayEvents() { }

    void PlayEvents::eventEmitter() {
      if (m_conf->getPlay()) {
        do {
          Event event;
          for (int i = 0; i < sizeof(event); i++) {
            ((char *)&event)[i] = getc(m_file);
            if ( ((char *)&event)[i] == -1) {
              fclose(m_file);
              m_file = NULL;
              break;
            }
          }
          if (m_file) {
            m_core->getInput()->clearInput();
            switch(event.event) {
              case InputEvent::EVENT_KEYDOWN:
                {
                  m_core->getInput()->setKeyState((PolyKEY )event.key, event.charCode, true, event.ticks); 
                }
                break;
              case InputEvent::EVENT_MOUSEWHEEL_UP:
                {
                  m_core->getInput()->mouseWheelUp(event.ticks);
                }
                break;
              case InputEvent::EVENT_MOUSEWHEEL_DOWN:
                {
                  m_core->getInput()->mouseWheelDown(event.ticks);
                }
                break;
              case InputEvent::EVENT_MOUSEDOWN:
                {
                  m_core->getInput()->setMouseButtonState(event.mouseButton, true, event.ticks);
                }
                break;
              case InputEvent::EVENT_MOUSEUP:
                {
                  m_core->getInput()->setMouseButtonState(event.mouseButton, false, event.ticks);
                }
              case InputEvent::EVENT_MOUSEMOVE:
                {
                  m_core->getInput()->setMousePosition(event.x, event.y, event.ticks);
                }
                break;
            }

            fprintf(stderr, "%f;%d;%d;%d;%d:%d:%d\n", event.dt, event.ticks, event.event, event.key, event.mouseButton, event.x, event.y);
          }
        } while(m_file);
      }
    }
  }
}

