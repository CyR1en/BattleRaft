#ifndef BATTLERAFT_INPUT_H
#define BATTLERAFT_INPUT_H

#include <string>
#include "Board.h"

namespace io {
    std::string ask_coord_input(ComputerBoard &p_board);

    std::string ask_input(const char *prompt);

    std::string generate_input_for_bot(Board &c_board);

    void pause(const char * prompt) ;

    void clear();
};

#endif
