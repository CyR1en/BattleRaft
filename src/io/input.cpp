#include "input.h"
#include "util.h"
#include <iostream>
#include <regex>

std::string io::ask_coord_input() {
    while (true) {
        std::string out = ask_input("Please enter a valid coordinate:");
        if (std::regex_match(out, std::regex(COORD_REGEX, std::regex_constants::icase)) || out == "exit")
            return out;
        std::cout << "That input is not valid ([A-J][0-10])" << std::endl;
    }
}

std::string io::ask_input(const char *prompt) {
    std::cout << prompt;
    std::string out;
    std::cin >> out;
    return out;
}