#ifndef BATTLERAFT_BITSET_H
#define BATTLERAFT_BITSET_H


#include <vector>
#include <iostream>

/**
 * Implementation of a Bitset.
 *
 * At its core, this class is basically just a binary, represented in a vector for easy processing.
 * That means, I implemented this class with the following binary properties in mind:
 * - Binary starts from right to left.
 * - You can do binary operations (although I only implemented an AND on this one).
 * - When you do an operation to different sized binary, it will pad the smaller number
 *   with zeros. i.e. (0101 0101) & (0101) -> (0101 0101) & (0000 0101)
 *
 * I tackled this problem this way to make it easier for me to compare Grids. Since this is going to
 * be the "row" for the Grid, I can just simply do an AND operand for each row and set the result of
 * the operation to be the i'th row on the output Grid.
 */
class Bitset : public std::vector<bool> {
private:
    // Variable for printing.
    const char *delimiter;

public:
    Bitset();

    Bitset(unsigned long size, bool val);

    // Override & bitwise operator.
    Bitset operator&(const Bitset &bs2);

    // Delimiter accessor.
    const char *getDelimiter() const;

    // Delimiter mutator.
    void setDelimiter(const char *_delimiter);

    // Get the same Bitset but with a different _delimiter.
    Bitset withDelimiterOf(const char *_delimiter) const;

    // Convert this bitset to decimal
    int toDecimal() const;

    // Overload stream insertion operator for printing.
    friend std::ostream &operator<<(std::ostream &out, const Bitset &b);
};


#endif
