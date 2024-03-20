#include <gtest/gtest.h>
#include <include/client.h>

// Define your test case
TEST(ClientTest, TestConnection) {
  // Create a Client object and perform test actions
  Client client("localhost", 8080);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}