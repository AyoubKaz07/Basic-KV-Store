#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "include/server.h"

// Empty test case
TEST(ServerTest, TestConnection) {
  Server server;
  server.RunServerSingleThreaded();
}

// Entry point for running the tests
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
