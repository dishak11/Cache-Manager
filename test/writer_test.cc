#include "../src/include/cache_main.h"
#include "../src/include/writer.h"
#include "gtest/gtest.h"

TEST(WriterTest, WriteItems) {
    // Set up a cache with a size of 2
    Cache cache(2);

    // Set up a vector of items to write
    std::vector<std::string> items = {"Item 1", "Item 2", "Item 3"};

    // Create test input files
    std::ofstream input("test_writer.txt");
    input << "1 New Item 1\n2 New Item 2\n" << std::endl;
    input.close();

    // Create a Writer object and call its write_items method
    Writer writer(cache, 0, "test_writer.txt");
    writer.write_items(items);

    // Verify that the cache has the correct values
    EXPECT_EQ(cache.get(0), "New Item 1");
    EXPECT_EQ(cache.get(1), "New Item 2");
}