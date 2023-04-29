#include "../src/include/cache_main.h"
#include "../src/include/reader.h"

#include <gtest/gtest.h>
#include <thread>

TEST(ReaderTest, ReadItems) {
    Cache cache(10);
    std::vector<std::string> items = {"foo", "bar", "baz", "qux", "quux", "corge", "grault", "garply", "waldo", "fred"};

    Reader reader(cache, 0, "input.txt", "output.txt");

    std::vector<std::thread> threads;
    threads.emplace_back([&] { reader.read_items(items); });
    threads.emplace_back([&] { reader.read_items(items); });
    threads.emplace_back([&] { reader.read_items(items); });
    threads.emplace_back([&] { reader.read_items(items); });

    for (auto& t : threads) {
        t.join();
    }

    std::ifstream output_file("output.txt");
    std::string line;

    std::vector<std::string> expected_output = {
        "foo Disk",
        "foo Cache",
        "bar Disk",
        "bar Cache",
        "baz Disk",
        "baz Cache",
        "qux Disk",
        "qux Cache",
        "quux Disk",
        "quux Cache",
        "corge Disk",
        "corge Cache",
        "grault Disk",
        "grault Cache",
        "garply Disk",
        "garply Cache",
        "waldo Disk",
        "waldo Cache",
        "fred Disk",
        "fred Cache"
    };

    size_t i = 0;
    while (std::getline(output_file, line)) {
        ASSERT_EQ(line, expected_output[i++]);
    }
}