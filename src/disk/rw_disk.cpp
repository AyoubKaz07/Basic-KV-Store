#include <fstream>
#include <string>
#include <unordered_map>
#include <iostream>
#include "include/rw_disk.h"

RWDisk::RWDisk(const std::string &filename) : file_name_(filename)
{
  file_.open(filename, std::ios::in | std::ios::out | std::ios::binary);
  if (!file_.is_open())
  {
    file_.clear();
    // File doesn't exist, create a new one
    file_.open(file_name_, std::ios::binary | std::ios::trunc | std::ios::out | std::ios::in);
    if (!file_.is_open())
    {
      std::cerr << "Failed to create file: " << filename << std::endl;
      return;
    }
    std::cout << "Created new file: " << filename << std::endl;
  }
}

RWDisk::~RWDisk()
{
  if (file_.is_open())
  {
    file_.close();
  }
}

void RWDisk::WriteKV(const std::string &key, const std::string &value)
{
  PrefixIO::WriteString(file_, key);
  PrefixIO::WriteString(file_, value);
}

std::string RWDisk::ReadKey()
{
  if (key_read_)
  {
    throw std::runtime_error("Key has been read");
  }

  std::string key = PrefixIO::ReadString(file_);
  key_read_ = true;
  return key;
}

std::string RWDisk::ReadValue()
{
  if (!key_read_)
  {
    throw std::runtime_error("Key has not been read");
  }

  std::string value = PrefixIO::ReadString(file_);
  if (file_.eof())
  {
    // Handle end of file
    throw std::runtime_error("End of file reached while reading value");
  }
  key_read_ = false;
  return value;
}

void RWDisk::SkipValue()
{
  // Check if a key has been read
  if (!key_read_)
  {
    // throw an exception
    throw std::runtime_error("Key has not been read");
  }
  int length = PrefixIO::ReadLength(file_);
  SkipBytes(length);
  key_read_ = false;
}

void RWDisk::SkipBytes(int bytes)
{
  // Get the current position of the get pointer
  std::streampos current_pos = file_.tellg();
  // Calculate the new position by adding the number of bytes to skip
  std::streampos new_pos = current_pos + static_cast<std::streamoff>(bytes);

  // Move the get pointer to the new position
  file_.seekg(new_pos);

  // Check if the seek operation was successful
  if (!file_)
  {
    // Handle error: Seek operation failed
    return;
  }
}

std::pair<std::string, std::string> RWDisk::NaiveKVLookup(const std::string &key)
{
  file_.clear();
  file_.seekg(0, std::ios::beg);
  while (file_.peek() != EOF)
  {
    std::string current_key = ReadKey();
    if (current_key.empty())
    {
      break;
    }
    if (current_key == key)
    {
      std::string value = ReadValue();
      return std::make_pair(current_key, value);
    }
    else
    {
      SkipValue();
    }
  }
  return std::make_pair("", "");
}

void RWDisk::Shutdown()
{
  if (file_.is_open())
  {
    file_.close();
  }
}