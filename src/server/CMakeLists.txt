# Set the source files for the Server component
file(GLOB SERVER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Create the library target for the Server component
add_library(server ${SERVER_SOURCES})

# Include directories for the Server component
target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)
