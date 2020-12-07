#ifndef BATTLERAFT_RAFT_H
#define BATTLERAFT_RAFT_H

#include "Bitset.h"
#include "util.h"

enum Orientation {
    H = 0,
    V = 1
};

std::ostream &operator<<(std::ostream &out, const Orientation &r);

class Raft : public Bitset {
private:
    int length;
    std::string type;
    Orientation orientation;

    Coord head;

public:
    Raft(std::string &type, int l, Orientation o, int x, int y);

    Raft(std::string &type, int l, Orientation o, const char *coord);

    int getLength() const;

    std::string getType() const;

    Orientation getOrientation() const;

    Coord getLocation() const;

    std::vector<Coord> getParts() const;

    void setLocation(const Coord &l);
};

std::ostream &operator<<(std::ostream &out, const Raft &r);

int getLengthWithName(const std::string &name);

#endif
