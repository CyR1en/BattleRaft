#include "Board.h"
#include "Raft.h"
#include <functional>
#include <algorithm>
#include <sstream>

/**
 * Board default constructor
 */
Board::Board() : BitGrid(10, 10) {}

/**
 * Attack the board using a coord.
 *
 * This checks if the coord param was used before to sink a raft.
 * If the attack on the coord, the raft on that coord will be then moved to the destroyed rafts.
 *
 * @param coord attack coord.
 */
void Board::attack(const Coord &coord) {
    //check if the coord already sunk a raft.
    for (const Raft &r : destroyed) {
        if (contains(r.getParts(), coord)) {
            std::cout << coord_to_string(coord) << " was already used to destroy the "
                      << r.getType() << "!" << std::endl;
            return;
        }
    }

    if (at(coord.getY()).at(coord.getX())) {
        hits.push_back(coord);
        for (Raft &r : rafts) {
            if (contains(r.getParts(), coord)) {
                std::cout << "The attack on " << coord_to_string(coord) << " sunk the " << r.getType() << std::endl;
                destroyed.push_back(r);
                break;
            }
        }
    } else {
        std::cout << "The attack on " << coord_to_string(coord) << " was a miss!" << std::endl;
        missed.push_back(coord);
    }
}

/**
 * Places a raft on the board.
 *
 * Checks if the raft cannot be placed on the board due to out of bounds.
 *
 * @param raft raft to be placed.
 * @param print_err if errors should be printed.
 */
void Board::placeRaft(const Raft &raft, bool print_err = true) {
    Coord coord = raft.getLocation();
    bool is_raft_h = raft.getOrientation() == H;

    //check bound
    bool is_out_bound = isRaftOutBound(raft);
    if (is_out_bound) {
        if (print_err)
            std::cout << "Cannot place " << raft.getOrientation() << " " << raft.getType() << " on "
                      << coord_to_string(raft.getLocation()) << " because it exceeds the board's boundary."
                      << std::endl;
        return;
    }
    //lambda to avoid usage of two for loops that does the exact same thing.
    auto lambda = is_raft_h ?
                  std::function<void(int)>{
                          [this, raft, coord](int location) { this->at(coord.getY()).at(location) = true; }} :
                  std::function<void(int)>{
                          [this, raft, coord](int location) { this->at(location).at(coord.getX()) = true; }};

    int start = is_raft_h ? coord.getX() : coord.getY();
    for (int i = start; i < (start + raft.getLength()); i++)
        lambda(i);
    rafts.push_back(raft);
}

/**
 * Checks if the raft is out of bounds before it's placed on the board.
 *
 * @param raft raft to be place.
 * @return if raft is out of bounds of the board.
 */
bool Board::isRaftOutBound(const Raft &raft) {
    bool is_raft_h = raft.getOrientation() == H;
    Coord coord = raft.getLocation();
    return is_raft_h ? (coord.getX() + raft.getLength()) > getWidth() - 1 :
           (coord.getY() + raft.getLength()) > getLength() - 1;;
}

//accessor
const std::vector<Coord> &Board::getHits() const {
    return hits;
}

//accessor
const std::vector<Coord> &Board::getMissed() const {
    return missed;
}

//accessor
const std::vector<Raft> &Board::getRafts() const {
    return rafts;
}

//accessor
const std::vector<Raft> &Board::getDestroyed() const {
    return destroyed;
}

/**
 * Renders all the destroyed raft on the board.
 *
 * used after rendering the board to finalize rendering of the board.
 *
 * @param p_rendered pre rendered board.
 * @return fully rendered board.
 */
std::vector<std::vector<std::string>> Board::renderDestroyed(std::vector<std::vector<std::string>> &p_rendered) const {
    for (const Raft &r : destroyed)
        for (Coord &c : r.getParts())
            p_rendered.at(c.getY()).at(c.getX()) = "x";
    return p_rendered;
}

/**
 * Renders the BitGrid to a displayable 2d vector of strings.
 *
 * This function only renders hits and missed and raft locations (not destroyed).
 * The pre-rendered board will then be passed to the function renderDestroyed() to finish rendering.
 *
 * @return rendered board.
 */
std::vector<std::vector<std::string>> Board::renderBoard() const {
    std::vector<std::vector<std::string>> rendered = std::vector<std::vector<std::string>>
            (size(), std::vector<std::string>(getWidth(), " "));
    for (int i = 0; i < size(); i++) {
        for (int j = 0; j < at(i).size(); j++) {
            std::stringstream ss;
            Coord coord(i, j);
            ss << (contains(getHits(), coord) ? "x" :
                   (contains(getMissed(), coord) ? "0" :
                    (at(j).at(i) ? "1" : "-")));
            rendered.at(j).at(i) = ss.str();
        }
    }
    return renderDestroyed(rendered);
}

/**
 * << operator overload for Board
 *
 * This inserts the rendered board to ostream.
 */
std::ostream &operator<<(std::ostream &out, const Board &b) {
    std::vector<std::vector<std::string>> rendered = b.renderBoard();
    for (int i = 0; i < b.size(); i++) {
        out << "| ";
        for (int j = 0; j < b.at(i).size(); j++) {
            out << rendered.at(i).at(j);
            out << ((j == (b.at(i).size() - 1)) ? "" : "  ");
        }
        auto end = i == b.size() ? " |" : " |\n";
        out << end;
    }
    return out;
}

/**
 * Returns all of the used coords on this board.
 *
 * used for input checking, so repeated inputs can be avoided.
 * @return all of the used coords on this board.
 */
std::vector<Coord> Board::getUsedCoords() {
    std::vector<Coord> used;
    for (Coord &c : missed)
        used.push_back(c);
    for (Raft &r : destroyed)
        for (Coord &r_p : r.getParts())
            used.push_back(r_p);
    return used;
}

/**
 * << operator overload for ComputerBoard
 *
 * This inserts the rendered board to ostream.
 */
std::ostream &operator<<(std::ostream &out, const ComputerBoard &b) {
    std::vector<std::vector<std::string>> rendered = b.renderBoard();
    for (int col = 0; col < b.getLength(); col++) {
        out << "| ";
        for (int row = 0; row < b.getWidth(); row++) {
            out << rendered.at(col).at(row);
            out << ((row == (b.getWidth() - 1)) ? "" : "  ");
        }
        auto end = col == b.getLength() ? " |" : " |\n";
        out << end;
    }
    return out;
}

/**
 * Override of the Board's render function.
 *
 * This does the exact same thing except showing the location of each raft.
 * Because the computer's raft placements must remain hidden.
 *
 * @return rendered ComputerBoard.
 */
std::vector<std::vector<std::string>> ComputerBoard::renderBoard() const {
    std::vector<std::vector<std::string>> rendered = std::vector<std::vector<std::string>>
            (size(), std::vector<std::string>(getWidth(), " "));
    for (int col = 0; col < getWidth(); col++) {
        for (int row = 0; row < getLength(); row++) {
            std::stringstream ss;
            Coord coord(col, row);
            ss << (contains(getHits(), coord) ? "x" :
                   (contains(getMissed(), coord) ? "0" : "-"));
            rendered.at(row).at(col) = ss.str();
        }
    }
    return renderDestroyed(rendered);
}

// BoardSetter class

/**
 * Set's the player's board.
 *
 * Using the CSVReader, parse all the raft on the csv file and iterate through all of the raft.
 * Checks if the raft is going to be out of bounds before placing.
 *
 * Using a temporary board and the & operator from the BitGrid, I can easily check if raft to be places is already
 * on the board.
 *
 * If both of the conditions above are not met then this will exit the program to allow the user to fix the input
 * file.
 *
 * @param board Board to set.
 * @param reader CSVReader to parse csv.
 */
void BoardSetter::setPlayerBoard(Board &board, CSVReader &reader) {
    Board temp_board;
    EnumParser<Orientation> o_parser;
    for (std::vector<std::string> &row : reader) {
        Raft r = Raft(row.at(0),
                      getLengthWithName(row.at(0)),
                      o_parser.parse_enum(row.at(2)),
                      row.at(1).c_str());
        if (temp_board.isRaftOutBound(r)) {
            std::cout << "Cannot place " << r.getOrientation() << " " << r.getType() << " on "
                      << coord_to_string(r.getLocation()) << " because it exceeds the board's boundary."
                      << std::endl;
            std::exit(0);
        }
        temp_board.placeRaft(r);
        if ((temp_board & board) > 0) {
            std::cout << "Cannot place " << r.getOrientation() << " " << r.getType() << " on "
                      << coord_to_string(r.getLocation()) << " because it intersects with a different raft."
                      << std::endl;
            std::exit(0);
        } else {
            board.placeRaft(r);
        }
        temp_board = Board();
    }
}

/**
 * Sets the computer's board.
 *
 * Iterate through all the raft that needs to be placed. Then generate a random orientation and using the
 * findValidCoord() function, generate a coord for the raft.
 *
 * @param c_board Board to set.
 */
void BoardSetter::setCompBoard(Board &c_board) {
    std::string types[] = {"Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"};
    for (std::string &t : types) {
        auto o = (Orientation) rand(0, 1);
        Coord coord = findValidCoord(c_board, t, o);
        c_board.placeRaft(Raft(t, getLengthWithName(t), o, coord.getX(), coord.getY()));
    }
}

/**
 * Find a valid coord for a raft.
 *
 * Based on the type and orientation of the raft, this checks if a raft with that attribute could be placed
 * on a board (with or without rafts in place).
 *
 * @param c_board board to find a coord in.
 * @param type type of raft.
 * @param o orientation of raft.
 * @return safe coordinate to place a raft with the param attributes.
 */
Coord BoardSetter::findValidCoord(Board &c_board, std::string &type, Orientation &o) {
    Board temp_board;
    while (true) {
        temp_board = Board();
        Coord rand_coord(rand(0, 9), rand(0, 9));
        Raft t_raft(type, getLengthWithName(type), o, rand_coord.getX(), rand_coord.getY());
        if (temp_board.isRaftOutBound(t_raft))
            continue;
        temp_board.placeRaft(t_raft, false);
        if (!((c_board & temp_board) > 0))
            return rand_coord;
    }
}
