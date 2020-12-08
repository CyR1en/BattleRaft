#include "input.h"
#include "util.h"
#include <iostream>
#include <regex>

/**
 * Function that asks for a coordinate input.
 *
 * Using regex this function validates if the input is actually a valid coordinate.
 * if not it goes through an infinite loop until a proper coordinate is entered.
 *
 * This function will also check if the input coord was used before.
 *
 * @param p_board The board to be attacked (which is the computer's)
 * @return Inputted coordinate
 */
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

/**
 * Ask for a string input.
 *
 * Plain and simple input prompt. No checks
 *
 * @param prompt Message to display for the prompt.
 * @return input.
 */
std::string io::ask_input(const char *prompt) {
    std::cout << prompt;
    std::string out;
    std::getline(std::cin, out);
    return out;
}

/**
 * Generate input for the bot.
 *
 * This function is just a way for the player to see the last rendered move. Without this, the whole would
 * just skip. So I'm forcing the player to hit enter so they have time to read the previous output.
 *
 * @param c_board your board to be attack by the bot.
 * @return input for the bot.
 */
std::string io::generate_input_for_bot(Board &c_board) {
    pause("Press enter to generate computer's attack . . .  \n");
    std::vector<Coord> used = c_board.getUsedCoords();
    while (true) {
        Coord coord = Coord(rand(0, 9), rand(0, 9));
        if (!contains(used, coord))
            return coord_to_string(coord);
    }
}

/**
 * A way to pause the console.
 * @param prompt message to show during pause.
 */
void io::pause(const char *prompt) {
    std::cin.clear();
    std::cout << prompt;
    std::cin.ignore();
}
