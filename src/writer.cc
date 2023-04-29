#include "include/writer.h"
#include <iostream>

/**
* Read a file and return a vector of indices and values. The file should be formatted as : index1 value1\n index2 value2
* here index starts from 1
*
* @param filename - Name of the file to read.
*/
std::vector<std::pair<int, std::string>> read_file(const std::string& filename) {
  std::vector<std::pair<int, std::string>> data;
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Error opening file: " << filename << '\n';
    return data;
  }
  std::string line;
  // Read the line from the file and store it in the data.
  while (std::getline(file, line)) {
    auto pos = line.find(' ');
    // Check if the current position is invalid.
    if (pos == std::string::npos) {
      std::cerr << "Invalid line: " << line << '\n';
      continue;
    }
    int index = std::stoi(line.substr(0, pos));
    std::string value = line.substr(pos + 1);
    data.emplace_back(index, value);
  }
  return data;
}

/**
* Write items to cache.
* 
* @param items
*/
void Writer::write_items(std::vector<std::string> &items) {
    std::vector<std::pair<int, std::string>> data = read_file(input_filename);
    for (const auto& [index, value] : data) {
        cache.put(index-1, value, true);
        items[index-1] = value;
    }
}