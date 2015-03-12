//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include <cstddef>
#include <stdexcept>
#include "History.hpp"

namespace Synthetics {
  namespace Constructor {
    History::History(int size) {
      m_cur = 0;
      m_size = size;
    }

    History::~History() {}

    void History::execute(Command *command) {
      command->execute();
      m_commands.push_back(command);
      ++m_cur;
      if (m_cur > m_size) {
        Command *command = m_commands.at(0);
        m_commands.erase(m_commands.begin());
        delete command;
      }
    }

    void History::undo() {
      if (m_cur > 0) {
        m_commands.at(m_cur-1)->undo();
        --m_cur;
      }
    }

    void History::redo() {
      if (m_cur < m_size) {
        ++m_cur;
        try {
        m_commands.at(m_cur-1)->execute();
        }
        catch (std::out_of_range &e) {
        }
      }
    }
  }
}

