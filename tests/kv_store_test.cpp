#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "include/kv_store.h"

// Empty test case
TEST(KeyValueStoreTest, SimpleInsertTest) {
  KeyValueStore kv_store;
  kv_store.set("key1", "value1");
  ASSERT_EQ(kv_store.get("key1"), "value1");
}

// Entry point for running the tests
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}