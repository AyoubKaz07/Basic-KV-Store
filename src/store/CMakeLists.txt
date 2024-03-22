# Set the source files for the KeyValueStore component
file(GLOB SERVER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Create the library target for the KeyValueStore component
add_library(KeyValueStore ${SERVER_SOURCES})

# Include directories for the KeyValueStore component
target_include_directories(KeyValueStore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)