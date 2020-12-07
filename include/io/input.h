#ifndef BATTLERAFT_INPUT_H
#define BATTLERAFT_INPUT_H

#include <string>

namespace io {
    std::string ask_coord_input();

    std::string ask_input(const char * prompt);
}

#endif
