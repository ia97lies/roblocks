//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_RECORDER_EVENT_H
#define SYNTHETICS_RECORDER_EVENT_H

namespace Synthetics {
  namespace Recorder {
    struct Event {
        int event;
        int key;
        wchar_t charCode;
        int mouseButton;
        int x;
        int y;
    };
  }
}

#endif
