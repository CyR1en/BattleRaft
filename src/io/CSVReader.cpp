#include "CSVReader.h"
#include <fstream>
#include "util.h"

/**
 * CSVReader constructor

 * @param path path to csv file to read.
 */
CSVReader::CSVReader(const char *path) : std::vector<std::vector<std::string>>(), path(path) {}

/**
 * Function that parse csv content.
 *
 * This opens the file and go through it line by line.
 * Since each line is formatted like "Element1,Element2,Element3", I just used the
 * tokenize function in utils to split the line using the delimiter ",".
 */
void CSVReader::parse() {
    std::ifstream csv_file(path);

    if (!csv_file.is_open()) {
        std::cout << "The csv path: [" << path << "] could not be opened" << std::endl;
        std::exit(0);
    }

    std::string line;
    while (std::getline(csv_file, line)) {
        std::vector<std::string> row;
        tokenize(line, row, ",");
        push_back(row);
    }
}

std::ostream &operator<<(std::ostream &out, const CSVReader &r) {
    for (const std::vector<std::string> &row : r) {
        for (const std::string &s : row)
            out << s << " ";
        out << std::endl;
    }
    return out;
}