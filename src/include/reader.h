#ifndef READER_H
#define READER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "cache_main.h"

/**
* @return A reference to the Reader class to facilitate chaining of calls to read_items
*/
class Reader {
public:
    Reader(Cache &cache, int id, const std::string &input_filename, const std::string &output_filename)
        : cache(cache), id(id), input_filename(input_filename), output_filename(output_filename) {}

    void read_items(const std::vector<std::string> &items);

private:
    Cache &cache;
    int id;
    std::string input_filename;
    std::string output_filename;
};

#endif // READER_H
