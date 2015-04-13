//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_RECORDER_EVENT_H
#define SYNTHETICS_RECORDER_EVENT_H

namespace Synthetics {
  namespace Recorder {
    struct Event {
      int ticks;
      int event;
      int key;
      int mouseButton;
      int x;
      int y;
      wchar_t charCode;
      float dt;
    };
  }
}

#endif
