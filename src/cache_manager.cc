#include "include/cache_manager.h"

/**
* Start the thread pool and read items from the file and write them to the file. This is called by the constructor
*/
void CacheManager::start() {
    std::vector<std::string> items = read_items_from_file(items_file);
    std::vector<std::thread> reader_threads;
    std::vector<std::thread> writer_threads;

    for (Reader &reader : readers) {
        reader_threads.emplace_back(&Reader::read_items, &reader, std::cref(items));
    }
    for (Writer &writer : writers) {
        writer_threads.emplace_back(&Writer::write_items, &writer, std::ref(items));
    }

    for (std::thread &t : reader_threads) {
        t.join();
    }
    for (std::thread &t : writer_threads) {
        t.join();
    }

    write_items_to_file(items_file, items);
}

/**
* Remove whitespace from the end of a string. This is equivalent to str. rstrip () except that it doesn't return a string instead of an empty string
* 
* @param str - The string to trim
*/
static inline void rtrim(std::string &str) {
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());
}

/**
* Read items from file. This is used to read Disk items from a file. The file should be formatted as value separated by \n.
* 
* @param filename - Name of file
*/
std::vector<std::string> CacheManager::read_items_from_file(const std::string &filename) {
    std::vector<std::string> items;
    std::ifstream input(filename);
    // Throws an error if the file is not found.
    if (!input.good()) {
        throw std::runtime_error("File not found: " + filename);
    }
    std::string line;
    // Get the next line from the input.
    while (std::getline(input, line)) {
        rtrim(line);
        items.push_back(line);
    }
    return items;
}

/**
* Write a list of items to a file.
* 
* @param filename - The name of the file to write to
* @param items - The items to write
*/
void CacheManager::write_items_to_file(const std::string &filename, const std::vector<std::string> &items) {
    std::ofstream output(filename);
    for (const std::string &item : items) {
        output << item << std::endl;
    }
}
