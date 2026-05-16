
cmake_minimum_required(VERSION 3.8)
project(audiosink-vcurrent-cpp)

# The Consumer MUST provide the SDK location
if (NOT DEFINED SDK_INCLUDE_DIR)
    message(FATAL_ERROR "SDK_INCLUDE_DIR is not defined.\n"
            "To build this library independently, you must provide the path to the RDK Android SDK headers.\n"
            "Example: cmake -DSDK_INCLUDE_DIR=/path/to/sdk/include .")
endif()

include_directories(${SDK_INCLUDE_DIR})

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_library(audiosink-vcurrent-cpp SHARED ${SRC_FILES})
target_include_directories(audiosink-vcurrent-cpp PUBLIC "include")
