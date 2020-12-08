#ifndef BATTLERAFT_BITGRID_H
#define BATTLERAFT_BITGRID_H


#include <vector>

#include "util.h"
#include "Bitset.h"

/**
 * Implementation of a BitGrid for Programming Assignment 2.
 *
 * This is an extension of a vector of a Bitset implementation that I made.
 * See documentation for Bitset to understand why I tackled the assignment this way.
 *
 * I made this class to extend a vector of Bitset because I want to inherit all of the
 * methods that are available in the class. All I needed to do was to implement the
 * required functions to complete the assignment. I also approached the comparison
 * by overriding the AND bit operator for this class (since the definition on canvas
 * seemed like it's just doing an AND operator).
 *
 * @see Bitset
 */
class BitGrid : public std::vector<Bitset> {
private:
    int length;
    int width;

    // Private recursive method to get a non 1 coordinate on the Grid.
    Coord &getRandNon1();

public:
    BitGrid(int _length, int _width);

    // Compare this grid with grid 2 and generate a new one that has 1
    // in every coord where this grid and grid2 have a 1s.
    BitGrid operator&(const BitGrid &grid2);

    bool operator>(const BitGrid &grid2);

    bool operator>(int decimal);

    // Fill 1/3rd of the grid with 1s.
    void fillThird();

    // length accessor.
    int getLength() const;

    // width accessor.
    int getWidth() const;

    // length mutator.
    void setLength(int length);

    // width mutator.
    void setWidth(int width);

    // Overload stream insertion operator for printing.
    friend std::ostream &operator<<(std::ostream &out, const BitGrid &g);
};

#endif
