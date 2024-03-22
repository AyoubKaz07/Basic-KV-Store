#include <gtest/gtest.h>
#include "include/rw_disk.h"

TEST(RWDiskTest, SimpleReadWriteTest)
{
  RWDisk rw_disk("test1.txt");

  // Write a key-value pair to the disk
  rw_disk.WriteKV("key1", "value1");

  std::pair<std::string, std::string> actual_pair = rw_disk.NaiveKVLookup("key1");
  std::pair<std::string, std::string> expected_pair("key1", "value1");
  ASSERT_EQ(actual_pair, expected_pair);
  
  ASSERT_EQ(rw_disk.NaiveKVLookup("key200"), std::make_pair(std::string(""), std::string("")));
  rw_disk.Shutdown();
}

TEST(RWDiskTest, NaiveKVLookupTest)
{
  RWDisk rw_disk("test2.txt");
  for (int i = 0; i < 200; i++)
  {
    std::string key = "key" + std::to_string(i);
    std::string value = "value" + std::to_string(i);
    rw_disk.WriteKV(key, value);
  }

  for (int i = 0; i < 200; i++)
  {
    std::string key = "key" + std::to_string(i);
    std::pair<std::string, std::string> actual_pair = rw_disk.NaiveKVLookup(key);
    std::pair<std::string, std::string> expected_pair(key, "value" + std::to_string(i));
    ASSERT_EQ(actual_pair, expected_pair);
  }
  rw_disk.Shutdown();
}


int main(int argc, char **argv)
{
  // Initialize Google Test
  ::testing::InitGoogleTest(&argc, argv);

  // Run the tests
  return RUN_ALL_TESTS();
}