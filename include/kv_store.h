#pragma once

#include <string>
#include <unordered_map>
#include <shared_mutex>
#include <mutex>

class KeyValueStore
{
private:
  std::unordered_map<std::string, std::string> store;
  std::shared_mutex mutex_;

public:
  // Method to set a key-value pair with string value
  void set(const std::string &key, const std::string &value);

  // Method to get the string value associated with a key
  std::string get(const std::string &key);

  // Method to delete a key-value pair
  void remove(const std::string &key);
};
