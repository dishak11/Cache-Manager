#include "include/cache_main.h"
#include "include/reader.h"
#include "include/writer.h"
#include "include/cache_manager.h"

#include <iostream>
#include <vector>
#include <stdexcept>

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
* Read filenames from file. This function is used to read a list of filenames from a file. The file should be formatted as a list of \n seperated file names.
* 
* @param filename - The name of the file to read from. \ return A list of filenames
*/
std::vector<std::string> read_filenames_from_file(const std::string &filename) {
    std::vector<std::string> filenames;

    std::ifstream input(filename);
    // Throws an error if the file is not found.
    if (!input.good()) {
        throw std::runtime_error("File not found: " + filename);
    }

    std::string line;
    // Get the line from the input and push it back to filenames.
    while (std::getline(input, line)) {
        rtrim(line);
        filenames.push_back(line);
    }
    return filenames;
}

/**
* Entry point for the cache. This is the main function that runs the cache manager. It takes 5 arguments : 
* 1. The size of the cache to be created. 
* 2. The file that has all filenames that are used to read.
* 3. The file that has all filenames that are used to write.
* 4. The file with all the data on Disk.
*
* @param argc
* @param argv
*/
int main(int argc, char *argv[]) {
    // Print out the usage message.
    if (argc != 5) {
        std::cerr << "Usage: " << "./cache <size_of_cache> <reader_file> <writer_file> <items_file>" << std::endl;
        return 1;
    }

    int cache_size = std::stoi(argv[1]);
    std::string reader_file = argv[2];
    std::string writer_file = argv[3];
    std::string items_file = argv[4];

    std::vector<std::string> reader_files = read_filenames_from_file(reader_file);
    std::vector<std::string> writer_files = read_filenames_from_file(writer_file);

    CacheManager cache_manager(cache_size, reader_files, writer_files, items_file);
    cache_manager.start();

    return 0;
}
