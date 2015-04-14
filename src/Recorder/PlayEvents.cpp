//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "unistd.h"
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
        m_core->getInput()->clearInput();
      }
    }

    PlayEvents::~PlayEvents() { }

    Number PlayEvents::emitEvent() {
      Number dt = -1;
      if (m_conf->getPlay() && m_file) {
        Event event;
        for (int i = 0; i < sizeof(event) && m_file; i++) {
          int c = fgetc(m_file);
          if (c == EOF) {
            fclose(m_file);
            m_file = NULL;
          }
          else {
            ((char *)&event)[i] = c;
          }
        }
        dt = event.dt;
        if (m_file) {
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
              break;
            case InputEvent::EVENT_MOUSEMOVE:
              {
                m_core->getInput()->setMousePosition(event.x, event.y, event.ticks);
                m_core->getInput()->setDeltaPosition(event.dx, event.dy);
              }
              break;
          }
          fprintf(stderr, "%f;%d;%d;%d;%d:%d:%d:%d:%d\n", event.dt, event.ticks, event.event, event.key, event.mouseButton, event.x, event.y, event.dx, event.dy);
        }
      }
      return dt;
    }
  }
}

