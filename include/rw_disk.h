/**
 * @file rw_disk.h
 * @brief Definitions and utilities for reading and writing key-value pairs to disk.
 *
 * This header file contains classes and utilities for storing and retrieving key-value pairs
 * on disk. The file format representation involves storing each key-value pair on a separate line,
 * with the key and value lengths, along with their respective data, delimited by end-of-line (EOL)
 * characters.
 *
 * Each key-value pair in the file is represented as follows:
 *   Key Length EOL Key Data Value Length EOL Value Data
 *
 * This format eases parsing of key-value pairs from the file, with the lengths
 * facilitating data retrieval and the EOL characters serving as delimiters between fields.
 */

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

class PrefixIO
{
private:
  static const char END_OF_LENGTH = '\x1A';
  static const char ESCAPE = '\x1B';

public:
  /**
   * @brief Writes the length of data to a file stream in a variable-length format.
   *
   * @param fs Reference to an std::fstream object representing the file stream.
   * @param length The length of the data to be written.
   */
  static void WriteLength(std::fstream &fs, int length)
  {
    int remaining = length;
    while (remaining > 0)
    {
      char b = static_cast<char>(remaining & 0xFF);
      // if EOL is part of the length, escape it
      if (b == END_OF_LENGTH || b == ESCAPE)
      {
        fs.put(ESCAPE);
      }
      fs.put(remaining & 0xFF);
      remaining >>= 8;
    }
    fs.put(END_OF_LENGTH);
  }

  /**
   * @brief Reads the length of data from a file stream in a variable-length format.
   *
   * @param fs Reference to an std::fstream object representing the file stream.
   * @return The length of the data read from the file stream.
   */
  static int ReadLength(std::fstream &fs)
  {
    int length = 0, index = 0;
    while (true)
    {
      int next = fs.get();
      if (next == END_OF_LENGTH)
      {
        break;
      }
      if (next == ESCAPE)
      {
        next = fs.get();
      }
      if (next < 0)
      {
        // throw end of stream exception
        throw std::runtime_error("Unexpected end of input stream");
      }
      length += (next << (8 * index++));
    }
    return length;
  }

  /**
   * @brief Writes a string to a file stream, preceded by its length.
   *
   * @param fs Reference to an std::fstream object representing the file stream.
   * @param str The string to be written to the file stream.
   */
  static void WriteString(std::fstream &fs, const std::string &str)
  {
    WriteLength(fs, str.length());
    fs.write(str.c_str(), str.length());
  }

  /**
   * @brief Reads a string from a file stream, assuming it was written using writeString.
   *
   * @param fs Reference to an std::fstream object representing the file stream.
   * @return The string read from the file stream.
   */
  static std::string ReadString(std::fstream &fs)
  {
    int length = ReadLength(fs);
    std::vector<char> buffer(length);
    fs.read(buffer.data(), length);
    return std::string(buffer.data(), buffer.size());
  }
};

class RWDisk
{
private:
  std::fstream file_;
  std::string file_name_;
  // Flag to check if the key has been read (used to skip the value when needed)
  bool key_read_ = false;

public:
  RWDisk(const std::string &filename);
  ~RWDisk();

  void WriteKV(const std::string &key, const std::string &value);
  std::string ReadKey();
  std::string ReadValue();
  std::pair<std::string, std::string> ReadKV();
  void SkipValue();
  void SkipBytes(int bytes);

  // Just trying out things, won't be use
  std::pair<std::string, std::string> NaiveKVLookup(const std::string &key);
  void Shutdown();
};
