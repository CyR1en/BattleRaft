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

/**
 * Converts an ordinal number to char.
 *
 * ie. 1 -> A, 2 -> B, 3 -> C.
 *
 * @param i number
 * @return char equivalent to the param.
 */
char ordinal_to_char(int i) {
    return char((i + 'A') - 1);
}

/**
 * Converts a Coord to a string representation of the coord.
 *
 * ie. (0,0) -> "A1"
 *
 * @param coord the coordinate to convert.
 * @return string version of the coordinate
 */
std::string coord_to_string(const Coord &coord) {
    std::stringstream ss;
    ss << char((0x0041) + coord.getX()) << coord.getY() + 1;
    return ss.str();
}

/**
 * Converts a string coord to an actual Coordinate.
 *
 * i.e "A1" -> (0,0)
 *
 * @param coord coord to convert
 * @return Coord version of the string coordinate
 */
Coord string_to_coord(const char *coord) noexcept(false) {
    if (!std::regex_match(coord, std::regex(COORD_REGEX, std::regex_constants::icase)))
        throw invalid_coord_syntax();

    std::string y = std::strlen(coord) == 3 ?
                    std::string(coord + 1, coord + 3) : std::string(coord + 1, coord + 2);
    return {char_to_ordinal(coord[0]) - 1, std::atoi(y.c_str()) - 1};
}

/**
 * Splits a string using a delimiter.
 *
 * @param str string to split
 * @param out vector to put each element
 * @param delimiter the delimiter to use.
 */
void tokenize(const std::string &str, std::vector<std::string> &out, const char * delimiter) {
    int start;
    int end = 0;
    while ((start = str.find_first_not_of(delimiter, end)) != std::string::npos) {
        end = str.find(delimiter, start);
        out.push_back(str.substr(start, end - start));
    }
}

/**
 * Platform dependent way to clear the screen.
 *
 * Not safe, but YOLO :)
 */
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
