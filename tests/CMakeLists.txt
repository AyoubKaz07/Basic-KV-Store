# GTest include code would
# go somewhere in here

find_package(GTest REQUIRED)

add_executable(kv_store_test kv_store_test.cpp)

target_link_libraries(kv_store_test PRIVATE GTest::GTest KeyValueStore)

add_test(kv_store_gtests kv_store_test)
