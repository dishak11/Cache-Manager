#ifndef WRITER_H
#define WRITER_H

#include <string>
#include <vector>
#include <fstream>
#include "cache_main.h"

/**
* @return A Writer that writes to a file.
*/
class Writer {
public:
    Writer(Cache &cache, int id, const std::string &input_filename)
        : cache(cache), id(id), input_filename(input_filename) {}

    void write_items(std::vector<std::string> &items);

private:
    Cache &cache;
    int id;
    std::string input_filename;
};

#endif // WRITER_H
