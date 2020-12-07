#ifndef BATTLERAFT_CSVREADER_H
#define BATTLERAFT_CSVREADER_H

#include <vector>
#include <iostream>

class CSVReader : public std::vector<std::vector<std::string>> {
private:
    const char * path;
public:
    explicit CSVReader(const char * path);

    void parse();
};

std::ostream &operator<<(std::ostream &out, const CSVReader &r);

#endif
