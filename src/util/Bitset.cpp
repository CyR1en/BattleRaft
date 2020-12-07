#include "Bitset.h"
#include <sstream>
#include <cmath>

using namespace std;

/**
 * Default constructor for this class.
 *
 * This just calls the constructor from the vector class.
 */
Bitset::Bitset() : delimiter(""), std::vector<bool>() {}

/**
 * Two  argument constructor for the Bitset class.
 *
 * This just uses the constructor from the vector class.
 *
 * @param size initial size of the vector.
 * @param val default value of each element in the vector.
 */
Bitset::Bitset(unsigned long size, bool val) : delimiter(""), std::vector<bool>(size, val) {}

/**
 * & operator overload for the Bitset class.
 *
 * This was implemented with the following properties of binary operations AND:
 * - Binary number starts from right to left.
 * - Shorter binary gets padded to have the same size as the bigger binary number.
 *
 * i.e:  1001 0011 & 1010 -> 1001 0011 & 0000 0010
 *
 * Since this is an AND operator, we can just ignore the extra bits that's being
 * operated with the padding.
 *
 * i.e: 1001 0011 & 1010 -> 1001 0011 & 0000 0010 = 0000 0010
 *
 * @param bs2 the other Bitset that this functions is going to do the operation with.
 * @return result of the AND operator between two Bitset.
 */
Bitset Bitset::operator&(const Bitset &bs2) {
    Bitset b2_local = bs2;

    Bitset *longer = size() > bs2.size() ? this : &b2_local;
    Bitset *shorter = longer == this ? &b2_local : this;

    auto longer_size = longer->size() - 1;
    auto shorter_size = shorter->size() - 1;

    // Make an empty Bitset with the size of the bigger Bitset
    Bitset out(longer->size(), false);
    // Then set elements to the result of the & operator between two bits
    for (int i = 0; i < shorter->size(); i++)
        out[(out.size() - 1) - i] = longer->at(longer_size - i) && shorter->at(shorter_size - i);

    return out;
}

/**
 * Returns this current Bitset with a different delimiter.
 *
 * I made this so that we could have a one liner when printing.
 * i.e: cout << bitset.withDelimiterOf(" ");
 *
 * This would not change the actual delimiter but instead makes a copy
 * and set that copy's delimiter.
 *
 * @param _delimiter New delimiter.
 * @return
 */
Bitset Bitset::withDelimiterOf(const char *_delimiter) const {
    Bitset copy = *this;
    copy.setDelimiter(_delimiter);
    return copy;
}

/**
 * ostream insertion operator overload for easy printing.
 *
 * @param out the output stream
 * @param b the Bitset to insert
 * @return ostream with the Bitset inserted.
 */
ostream &operator<<(ostream &out, const Bitset &b) {
    for (int i = 0; i < (int) b.size(); i++)
        out << (i >= 0 && b.at(i)) << (i == b.size() - 1 ? "" : b.getDelimiter());
    return out;
}

/**
 * Delimiter accessor.
 *
 * @return delimiter.
 */
const char *Bitset::getDelimiter() const {
    return delimiter;
}

/**
 * Delimiter mutator.
 *
 * @param _delimiter new delimiter.
 */
void Bitset::setDelimiter(const char *_delimiter) {
    delimiter = _delimiter;
}

int Bitset::toDecimal() const {
    int out = 0;
    for (int i = 0; i < size(); i++)
        out += at((size() - 1) - i) * (pow(2, i));
    return out;
}






