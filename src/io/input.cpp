#include "input.h"
#include "util.h"
#include <iostream>
#include <regex>

std::string io::ask_coord_input(ComputerBoard &p_board) {
    std::vector<Coord> used = p_board.getUsedCoords();
    while (true) {
        std::string out = ask_input("Please enter a valid coordinate: ");
        if (out == "exit")
            return out;

        if (std::regex_match(out, std::regex(COORD_REGEX, std::regex_constants::icase))) {
            Coord c = string_to_coord(out.c_str());
            if (!contains(used, c))
                return out;
            else
                std::cout << out << " was used before or a part of a destroyed raft." << std::endl;
        } else
            std::cout << "That input is not valid ([A-J][0-10])" << std::endl;
    }
}

std::string io::ask_input(const char *prompt) {
    std::cout << prompt;
    std::string out;
    std::getline(std::cin, out);
    return out;
}

std::string io::generate_input_for_bot(Board &c_board) {
    pause("Press enter to generate computer's attack . . .  \n");
    std::vector<Coord> used = c_board.getUsedCoords();
    while (true) {
        Coord coord = Coord(rand(0, 9), rand(0, 9));
        if (!contains(used, coord))
            return coord_to_string(coord);
    }
}

void io::pause(const char *prompt) {
    try {
        std::cin.clear();
        std::cout << prompt;
        std::cin.ignore();
    } catch (...) {

    }

}
