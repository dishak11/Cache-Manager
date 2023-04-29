#ifndef CACHE_H
#define CACHE_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <mutex>
#include <algorithm>

/**
* @return A cache with the given size. It is an error to call this if the cache is uninitialized
*/
class Cache {
public:
    Cache(int size) : size(size) {}

    std::string get(int key);
    void put(int key, const std::string &value, bool is_dirty = false);
    bool is_dirty(int key);

private:
    using KeyIterator = std::list<int>::iterator;

    void touch(std::unordered_map<int, std::pair<std::string, KeyIterator>>::iterator it);

    int size;
    std::list<int> keys;
    std::unordered_map<int, std::pair<std::string, KeyIterator>> cache;
    std::unordered_set<int> dirty_keys;
    std::mutex cache_mtx;
};

#endif // CACHE_H
