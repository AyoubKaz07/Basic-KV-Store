# GTest include code would
# go somewhere in here

find_package(GTest REQUIRED)

add_executable(kv_store_test kv_store_test.cpp)
add_executable(rw_disk_test rw_disk_test.cpp)

target_link_libraries(kv_store_test PRIVATE GTest::GTest KeyValueStore)
target_link_libraries(rw_disk_test PRIVATE GTest::GTest RWDisk)

add_test(kv_store_gtests kv_store_test)
add_test(rw_disk_gtests rw_disk_test)
