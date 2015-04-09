//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#ifndef SYNTHETICS_SHOWKEYHITS_KEYLABEL_H
#define SYNTHETICS_SHOWKEYHITS_KEYLABEL_H

#include "Polycode.h"
#include <string>

namespace Synthetics {
  namespace ShowKeyHits {

    class KeyLabel : public Polycode::SceneLabel {
      public:
        KeyLabel();
        virtual ~KeyLabel(); 
        void setLabel(std::string text);
        void update(Number dt);

      private:
        bool m_active;
        bool m_fade;
        Number m_elapsed;
    };
  }
}

#endif
