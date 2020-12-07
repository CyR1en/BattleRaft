#ifndef BATTLERAFT_UTIL_H
#define BATTLERAFT_UTIL_H

#include <iostream>
#include <random>
#include <regex>
#include <vector>
#include <map>

// A Uniform Distribution template to aid #rand() with templating.
// Defines uniform_distribution in compile time.
template<class T>
using uniform_distribution =
typename std::conditional<
        std::is_floating_point<T>::value,
        std::uniform_real_distribution<T>,
        typename std::conditional<
                std::is_integral<T>::value,
                std::uniform_int_distribution<T>,
                void
        >::type
>::type;

// Template function to generate a random generic type number from  a to b.
template<typename T>
T rand(T a, T b) {
    std::mt19937 engine(std::random_device{}()); // engine and seed it with rd;
    uniform_distribution<T> rangeDist(a, b); // [a, b] range distribution
    return rangeDist(engine);
}

template<typename T>
class EnumParser {
    std::map<std::string, T> enumMap;
public:
    EnumParser();

    T parse_enum(const std::string &value) {
        typename std::map<std::string, T>::const_iterator iValue = enumMap.find(value);
        if (iValue == enumMap.end())
            throw std::exception("Invalid key");
        return iValue->second;
    }
};

template<typename C, typename T>
auto contains(const C &v, const T &x) -> decltype(end(v), true) {
    return end(v) != std::find(begin(v), end(v), x);
}

/**
 * Class that represents a point on a Cartesian Plane.
 */
template<class T = int>
class Point {
private:
    T x_;
    T y_;
public:
    // Constructor
    Point(T x, T y) : x_{x}, y_{y} {}

    // Immutable accessor.
    T getX() const {
        return x_;
    }

    // Immutable accessor.
    T getY() const {
        return y_;
    }

    void setX(double x) {
        x_ = x;
    }

    void setY(double y) {
        y_ = y;
    }

    friend std::ostream &operator<<(std::ostream &out, const Point &g) {
        out << "(" << g.getX() << ", " << g.getY() << ")";
        return out;
    }

};

template<typename T>
inline bool operator==(const Point<T> &lhs, const Point<T> &rhs) {
    return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
}

typedef Point<> Coord;

#define ALPHABET_REGEX "[A-Ja-j]"
#define COORD_REGEX "([A-Z])(10|[0-9])"

// Utility function that converts chars to ordinal number
int char_to_ordinal(char ch);

char ordinal_to_char(int i);

std::string coord_to_string(const Coord &coord);

Coord string_to_coord(const char *coord) noexcept(false);

void tokenize(const std::string &str, std::vector<std::string> &out, const char *delimiter);

void clear_screen();

#endif
