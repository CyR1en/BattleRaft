#include "CSVReader.h"
#include <fstream>
#include "util.h"

CSVReader::CSVReader(const char *path) : std::vector<std::vector<std::string>>(), path(path) {}

void CSVReader::parse() {
    std::ifstream csv_file(path);

    if (!csv_file.is_open()) {
        std::cout << "The csv path: [" << path << "] could not be opened";
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