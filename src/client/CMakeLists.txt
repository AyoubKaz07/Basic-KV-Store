# Set the source files for the Client component
file(GLOB CLIENT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Create the library target for the Client component
add_library(client ${CLIENT_SOURCES})

# Include directories for the Client component
target_include_directories(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)
