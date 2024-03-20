#include "include/kv_store.h"

void KeyValueStore::set(const std::string& key, const std::string& value) {
    store[key] = value;
}

// Method to get the string value associated with a key
std::string KeyValueStore::get(const std::string& key) {
    if (store.find(key) != store.end()) {
        return store[key];
    } else {
        return ""; // Return empty string if key not found
    }
}

// Method to delete a key-value pair
void KeyValueStore::remove(const std::string& key) {
    store.erase(key);
}
