# GTest include code would
# go somewhere in here

find_package(GTest REQUIRED)

add_executable(client_test client_test.cpp)
add_executable(server_test server_test.cpp)

target_link_libraries(client_test PRIVATE GTest::GTest client)
target_link_libraries(server_test PRIVATE GTest::GTest server)

add_test(client_gtests client_test)
add_test(server_gtests server_test)
