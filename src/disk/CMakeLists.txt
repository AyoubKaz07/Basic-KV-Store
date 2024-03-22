# Set the source files for the RWDisk component
file(GLOB SERVER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Create the library target for the RWDisk component
add_library(RWDisk ${SERVER_SOURCES})

# Include directories for the RWDisk component
target_include_directories(RWDisk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)