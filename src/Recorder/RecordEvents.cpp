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
        switch(e->getEventCode()) {
          case InputEvent::EVENT_KEYDOWN:
            {
              int keyCode = inputEvent->keyCode();
              wchar_t keyCharCode = inputEvent->getCharCode();
              int ticks = m_core->getTicks();
              // TODO: write it down in a file 
            }
            break;
          case InputEvent::EVENT_MOUSEDOWN:
            {
              int button = inputEvent->getMouseButton();
              // TODO: write it down in a file 
              int ticks = m_core->getTicks();
            }
            break;
        }
      }
    }

    void RecordEvents::update(Number dt) {
      // XXX: What shall I do here and how can I replay this in the end?
      // I somehow would need to wrap up Update in SyntheticsApp.cpp
      // => In play mode I'm the event source and the frame rate source!
    }

    void RecordEvents::activate(bool on) {
      if (on) {
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
        m_core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
      }
      else if (!on) {
        m_core->getInput()->removeEventListener(this, InputEvent::EVENT_KEYDOWN);
        m_core->getInput()->removeEventListener(this, InputEvent::EVENT_MOUSEDOWN);
      }
    }

  }
}
