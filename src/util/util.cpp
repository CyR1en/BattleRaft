//
// Created by Ethan Bacurio on 11/24/20.
//

#include "util.h"
#include <sstream>

/**
 * Utility function to convert alphabetical characters to ordinal number.
 *
 * This checks input by using regex and checking if the argument is a valid letter
 * in the alphabet (including all cases).
 *
 * @param ch character to convert to an ordinal number.
 * @return Ordinal number of the character.
 */
int char_to_ordinal(char ch) {
    return std::regex_match(std::string(1, ch), std::regex(ALPHABET_REGEX)) ?
           std::tolower(ch) - 0x0061 + 1 : 0;
}

char ordinal_to_char(int i) {
    return char((i + 'A') - 1);
}

std::string coord_to_string(const Coord &coord) {
    std::stringstream ss;
    ss << char((0x0041) + coord.getX()) << coord.getY() + 1;
    return ss.str();
}

Coord string_to_coord(const char *coord) noexcept(false) {
    if (!std::regex_match(coord, std::regex(COORD_REGEX, std::regex_constants::icase)))
        throw std::exception("Invalid coordinate syntax.");

    std::string y = std::strlen(coord) == 3 ?
                    std::string(coord + 1, coord + 3) : std::string(coord + 1, coord + 2);
    return {char_to_ordinal(coord[0]) - 1, std::atoi(y.c_str()) - 1};
}

void tokenize(const std::string &str, std::vector<std::string> &out, const char * delimiter) {
    int start;
    int end = 0;
    while ((start = str.find_first_not_of(delimiter, end)) != std::string::npos) {
        end = str.find(delimiter, start);
        out.push_back(str.substr(start, end - start));
    }
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
