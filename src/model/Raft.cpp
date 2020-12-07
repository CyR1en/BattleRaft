#include "Raft.h"

template<>
EnumParser<Orientation>::EnumParser() {
    enumMap["H"] = H;
    enumMap["V"] = V;
}

Raft::Raft(std::string &t, int l, Orientation o, int x, int y) : Bitset(l, true), type(t), length(l),
                                                                 orientation(o), head(x, y) {}

Raft::Raft(std::string &t, int l, Orientation o, const char *coord) : Bitset(l, true), type(t), length(l),
                                                                      orientation(o), head(11, 11) {
    try {
        head = string_to_coord(coord);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

int Raft::getLength() const {
    return length;
}

std::string Raft::getType() const {
    return type;
}

Orientation Raft::getOrientation() const {
    return orientation;
}

Coord Raft::getLocation() const {
    return head;
}

void Raft::setLocation(const Coord &l) {
    head = l;
}

std::vector<Coord> Raft::getParts() const {
    std::vector<Coord> parts;
    parts.push_back(head);
    bool is_h = orientation == H;
    if(is_h) {
        for(int i = 1; i < length; i++) {
            parts.emplace_back(head.getX() + i, head.getY());
        }
    } else {
        for(int i = 1; i < length; i++) {
            parts.emplace_back(head.getX(), head.getY() + i);
        }
    }
    return parts;
}

// operator overloads
std::ostream &operator<<(std::ostream &out, const Raft &r) {
    out << r.getType() << " " << coord_to_string(r.getLocation()) << " " << r.getOrientation();
    return out;
}

std::ostream &operator<<(std::ostream &out, const Orientation &orientation) {
    switch (orientation) {
        case H:
            out << "H";
            break;
        case V:
            out << "V";
            break;
    }
    return out;
}

int getLengthWithName(const std::string &name) {
    if (name == "Carrier")
        return 5;
    else if (name == "Battleship")
        return 4;
    else if (name == "Cruiser" || name == "Submarine")
        return 3;
    else if (name == "Destroyer")
        return 2;
    return 0;
}

