#include "Board.h"
#include "Raft.h"
#include <functional>
#include <algorithm>
#include <sstream>

Board::Board() : BitGrid(10, 10) {}

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

bool Board::isRaftOutBound(const Raft &raft) {
    bool is_raft_h = raft.getOrientation() == H;
    Coord coord = raft.getLocation();
    return is_raft_h ? (coord.getX() + raft.getLength()) > getWidth() - 1 :
           (coord.getY() + raft.getLength()) > getLength() - 1;;
}

const std::vector<Coord> &Board::getHits() const {
    return hits;
}

const std::vector<Coord> &Board::getMissed() const {
    return missed;
}

const std::vector<Raft> &Board::getRafts() const {
    return rafts;
}

const std::vector<Raft> &Board::getDestroyed() const {
    return destroyed;
}

std::vector<std::vector<std::string>> Board::renderDestroyed(std::vector<std::vector<std::string>> &p_rendered) const {
    for (const Raft &r : destroyed)
        for (Coord &c : r.getParts())
            p_rendered.at(c.getY()).at(c.getX()) = "x";
    return p_rendered;
}

std::vector<std::vector<std::string>> Board::renderBoard() const {
    std::vector<std::vector<std::string>> rendered = std::vector<std::vector<std::string>>
            (size(), std::vector<std::string>(getWidth(), " "));
    for (int i = 0; i < size(); i++) {
        for (int j = 0; j < at(i).size(); j++) {
            std::stringstream ss;
            Coord coord(i, j);
            ss << (contains(getHits(), coord) ? "x" :
                   (contains(getMissed(), coord) ? "0" :
                    (at(j).at(i) ? "1" : "~")));
            rendered.at(j).at(i) = ss.str();
        }
    }
    return renderDestroyed(rendered);
}

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

std::vector<Coord> Board::getUsedCoords() {
    std::vector<Coord> used;
    for (Coord &c : missed)
        used.push_back(c);
    for (Raft &r : destroyed)
        for (Coord &r_p : r.getParts())
            used.push_back(r_p);
    return used;
}


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

std::vector<std::vector<std::string>> ComputerBoard::renderBoard() const {
    std::vector<std::vector<std::string>> rendered = std::vector<std::vector<std::string>>
            (size(), std::vector<std::string>(getWidth(), " "));
    for (int col = 0; col < getWidth(); col++) {
        for (int row = 0; row < getLength(); row++) {
            std::stringstream ss;
            Coord coord(col, row);
            ss << (contains(getHits(), coord) ? "x" :
                   (contains(getMissed(), coord) ? "0" : "~"));
            rendered.at(row).at(col) = ss.str();
        }
    }
    return renderDestroyed(rendered);
}

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
        } else {
            board.placeRaft(r);
        }
        temp_board = Board();
    }
}

void BoardSetter::setCompBoard(Board &c_board) {
    std::string types[] = {"Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"};
    for (std::string &t : types) {
        auto o = (Orientation) rand(0, 1);
        Coord coord = findValidCoord(c_board, t, o);
        c_board.placeRaft(Raft(t, getLengthWithName(t), o, coord.getX(), coord.getY()));
    }
}

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
