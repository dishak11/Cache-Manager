#include "include/reader.h"

/**
* Read items from cache and write to file.
* 
* @param items
*/
void Reader::read_items(const std::vector<std::string> &items) {
    std::ifstream input(input_filename);
    // Throws an error if the input is not good.
    if (!input.good()) {
        throw std::runtime_error("File not found: " + input_filename);
    }
    std::ofstream output(output_filename);
    int index;
    // Output the contents of the input.
    while (input >> index) {
        std::string value = cache.get(index-1);
        // Write out the value of the item.
        if (value.empty()) {
            value = items[index-1];
            cache.put(index-1, value);
            output << value << " Disk" << std::endl;
        } else {
            output << value << " Cache" << std::endl;
        }
    }
}
