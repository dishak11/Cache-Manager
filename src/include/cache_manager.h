#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <thread>
#include "cache_main.h"
#include "reader.h"
#include "writer.h"

/**
* @return A CacheManager with the given cache size, reader files, writer files and item file
*/
class CacheManager {
public:
    CacheManager(int cache_size, const std::vector<std::string> &reader_files, const std::vector<std::string> &writer_files, const std::string &items_file)
        : cache(cache_size), items_file(items_file)
    {
        // Emplace back the cache.
        for (size_t i = 0; i < reader_files.size(); ++i) {
            std::string output_filename = reader_files[i].substr(0, reader_files[i].length() - 4) + "_out.txt";
            readers.emplace_back(cache, i, reader_files[i], output_filename);
        }
        // Emplace the writer files back to the cache.
        for (size_t i = 0; i < writer_files.size(); ++i) {
            writers.emplace_back(cache, i, writer_files[i]);
        }
    }
    void start();

private:
    std::vector<std::string> read_items_from_file(const std::string &filename);
    void write_items_to_file(const std::string &filename, const std::vector<std::string> &items);

    Cache cache;
    std::vector<Reader> readers;
    std::vector<Writer> writers;
    std::string items_file;
};

#endif  // CACHEMANAGER_H
