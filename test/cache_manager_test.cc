#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include "../src/include/cache_main.h"
#include "../src/include/writer.h"
#include "../src/include/cache_manager.h"
#include "../src/include/reader.h"

// trim from end (in place)
static inline void rtrim(std::string &str) {
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());
}

std::vector<std::string> read_filenames_from_file(const std::string &filename) {
    std::vector<std::string> filenames;
    std::ifstream input(filename);
    std::string line;
    // check for case where no space or many space at end
    while (std::getline(input, line)) {
        rtrim(line);
        filenames.push_back(line);
    }
    return filenames;
}

std::vector<std::string> read_items_from_file(const std::string &filename) {
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

// Test fixture for CacheManager tests
class CacheManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create test files
        std::ofstream items_file("test_items.txt");
        items_file << "item1\nitem2\nitem3\n";
        items_file.close();

        std::ofstream reader_file("test_readers.txt");
        reader_file << "test_reader1.txt\ntest_reader2.txt\n";
        reader_file.close();

        std::ofstream writer_file("test_writers.txt");
        writer_file << "test_writer1.txt\ntest_writer2.txt\n";
        writer_file.close();

        // Create test input files
        std::ofstream reader1("test_reader1.txt");
        reader1 << "2\n1\n3\n";
        reader1.close();

        std::ofstream reader2("test_reader2.txt");
        reader2 << "3\n";
        reader2.close();

        std::ofstream writer1("test_writer1.txt");
        writer1 << "2 item_21\n";
        writer1.close();

        std::ofstream writer2("test_writer2.txt");
        writer2 << "1 item_12\n3 item_32\n";
        writer2.close();
    }

    void TearDown() override {
        // Remove test files
        std::remove("test_items.txt");
        std::remove("test_readers.txt");
        std::remove("test_writers.txt");
        std::remove("test_reader1.txt");
        std::remove("test_reader2.txt");
        std::remove("test_writer1.txt");
        std::remove("test_writer2.txt");
    }
};

TEST_F(CacheManagerTest, TestCacheManager) {
    // Arrange
    int cache_size = 2;
    std::vector<std::string> reader_files = read_filenames_from_file("test_readers.txt");
    std::vector<std::string> writer_files = read_filenames_from_file("test_writers.txt");
    std::string items_file = "test_items.txt";

    // Act
    CacheManager cache_manager(cache_size, reader_files, writer_files, items_file);
    cache_manager.start();

    // Assert
    std::vector<std::string> expected_items = {"item_12", "item_21", "item_32"};
    std::vector<std::string> actual_items = read_items_from_file(items_file);
    EXPECT_EQ(expected_items, actual_items);
}