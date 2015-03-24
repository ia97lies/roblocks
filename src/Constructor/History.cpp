//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "stdio.h"
#include <cstddef>
#include <stdexcept>
#include "History.hpp"

namespace Synthetics {
  namespace Constructor {
    History::History(int size) {
      m_cur = 0;
      m_size = size;
    }

    History::~History() {
       for (int i = 0; i < m_commands.size(); i++) {
         Command *command = m_commands.at(i);
         delete command;
       }
    }

    void History::execute(Command *command) {
      command->execute();
      if (m_cur >= m_size) {
        --m_cur;
        Command *command = m_commands.at(0);
        m_commands.erase(m_commands.begin());
        delete command;
      }
      if (m_cur < m_commands.size()) {
        for (int i = m_cur; i < m_commands.size(); i++) {
          Command *command = m_commands.at(i);
          delete command;
        }
        m_commands.erase(m_commands.begin()+m_cur, m_commands.end());
      }
      m_commands.push_back(command);
      ++m_cur;
    }

    void History::undo() {
      if (m_cur > 0) {
        --m_cur;
        m_commands.at(m_cur)->undo();
      }
    }

    void History::redo() {
      if (m_cur < m_size) {
        try {
          m_commands.at(m_cur)->execute();
          ++m_cur;
        }
        catch (std::out_of_range &e) {}
      }
    }
  }
}

