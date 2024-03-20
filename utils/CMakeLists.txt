file(GLOB UTILS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Add the source files in the utils directory
add_library(utils io_utils.cpp)

# Include the headers directory
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)