#include "include/kv_store.h"
#include <shared_mutex>
#include <iostream>

void KeyValueStore::set(const std::string& key, const std::string& value) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    store[key] = value;
}

std::string KeyValueStore::get(const std::string& key) {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    if (store.find(key) != store.end()) {
        return store[key];
    } else {
        return ""; // Return empty string if key not found (can be customized)
    }
}

void KeyValueStore::remove(const std::string& key) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    store.erase(key);
}