#include "include/cache_main.h"

/**
* Returns true if the key is in the cache and false otherwise. This function is a thread safe way implemented with mutex.
* 
* @param key - The key to look up in the cache. It must be an integer.
*/
std::string Cache::get(int key) {
    std::unique_lock<std::mutex> lock(cache_mtx);
    auto it = cache.find(key);
    // Returns the first item in the cache.
    if (it != cache.end()) {
        touch(it);
        return it->second.first;
    }
    return "";
}

/**
* Put a value into the cache. If the key is already present it will be updated to the new value
* 
* @param key - The key to store the value under
* @param value - Value to store
* @param is_dirty - is_dirty Whether or not the is dirty
*/
void Cache::put(int key, const std::string &value, bool is_dirty) {
    std::unique_lock<std::mutex> lock(cache_mtx);
    auto it = cache.find(key);
    // If the cache is end touch the cache.
    if (it != cache.end()) {
        touch(it);
    } else {
        // Removes the keys from the cache.
        if (keys.size() >= static_cast<size_t>(size)) {
            cache.erase(keys.back());
            keys.pop_back();
        }
        keys.push_front(key);
    }
    cache[key] = {value, keys.begin()};
    // Inserts or erases the key if is_dirty.
    if (is_dirty) dirty_keys.insert(key);
    else dirty_keys.erase(key);
}

/**
* Check if a key is dirty. This is used to prevent deadlocks in Cache :: get () and Cache :: put ()
* 
* @param key - The key to check.
* 
* @return True if the key is dirty false otherwise. Note that the cache_mtx is locked by the caller
*/
bool Cache::is_dirty(int key) {
    std::unique_lock<std::mutex> lock(cache_mtx);
    return dirty_keys.find(key) != dirty_keys.end();
}

/**
* Touch the key to make sure it is in the cache. This is called by Cache :: get ()
* 
* @param it - Iterator to the key
*/
void Cache::touch(std::unordered_map<int, std::pair<std::string, KeyIterator>>::iterator it) {
    int key = it->first;
    keys.erase(it->second.second);
    keys.push_front(key);
    it->second.second = keys.begin();
}
