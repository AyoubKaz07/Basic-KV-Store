#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "include/kv_store.h"


TEST(KeyValueStoreTest, SimpleInsertTest) {
  KeyValueStore kv_store;
  kv_store.set("key1", "value1");
  ASSERT_EQ(kv_store.get("key1"), "value1");
}

TEST(KeyValueStoreTest, SimpleDeleteTest) {
  KeyValueStore kv_store;
  kv_store.set("key1", "value1");
  kv_store.remove("key1");
  ASSERT_EQ(kv_store.get("key1"), "");
}

// gdb -ex r --args ./tests/kv_store_test --gtest_filter=KeyValueStoreTest.MultiThreadedReadWriteTest
// break KeyValueStoreTest_MultiThreadedReadWriteTest_Test::TestBody()

// Terrible test
/*TEST(KeyValueStoreTest, MultiThreadedReadWriteTest) {
  KeyValueStore kv_store;
  std::thread t1([&kv_store](){
    std::cout << "Setting key1\n";
    kv_store.set("key1", "value1");
  });
  std::thread t2([&kv_store](){
    std::cout << "Getting key1\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    ASSERT_EQ(kv_store.get("key1"), "");
  });
  std::thread t3([&kv_store](){
    std::cout << "Removing key1\n";
    kv_store.remove("key1");
    ASSERT_EQ(kv_store.get("key1"), "");
  });
  t1.join();
  t2.join();
  t3.join();
}*/

TEST(KeyValueStoreTest, RaceConditionTest) {
  KeyValueStore kv_store;
  std::thread t1([&kv_store](){
    kv_store.set("key1", "value1");
  });
  std::thread t2([&kv_store](){
    kv_store.set("key2", "value2");
  });
  t1.join();
  t2.join();
  ASSERT_EQ(kv_store.get("key1"), "value1");
  ASSERT_EQ(kv_store.get("key2"), "value2");
}

// This doesn't necessarily succeed, depends on how the threads are scheduled
TEST(KeyValueStoreTest, DISABLED_ConcurrencyTest) {
  KeyValueStore kv_store;

  // Define the number of threads for simultaneous read and write operations
  const int num_threads = 10;
  std::vector<std::thread> threads;

  // Insert a key-value pair
  kv_store.set("key", "value");

  // Simultaneously delete and read the key-value pair in multiple threads
  for (int i = 0; i < num_threads; ++i) {
    threads.emplace_back([&kv_store]() {
      // Delete the key-value pair
      kv_store.remove("key");
    });

    threads.emplace_back([&kv_store]() {
      // Read the key-value pair
      std::string value = kv_store.get("key");
      std::cout << "Value: " << value << std::endl;
      // Assert that the value is empty, indicating that the pair was deleted
      ASSERT_EQ(value, "");
    });
  }

  // Join all threads
  for (auto& thread : threads) {
    thread.join();
  }
}


// Entry point for running the tests
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}