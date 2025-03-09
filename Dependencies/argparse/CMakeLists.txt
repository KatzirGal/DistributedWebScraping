cmake_minimum_required(VERSION 3.20)
project(argparseDependency)

include(FetchContent)

# Declare argparse
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
    GIT_TAG v2.4  # Latest stable release
)

# Fetch and make argparse available
FetchContent_MakeAvailable(argparse)

# Create an interface library for argparse
add_library(argparse_lib INTERFACE)

# FetchContent places argparse in `_deps`, so we must use the correct variable:
target_include_directories(argparse_lib INTERFACE ${CMAKE_SOURCE_DIR}/Dependencies/CMAKE_BUILD/_deps/argparse-src/include)

message(STATUS "argparse headers are located in: ${CMAKE_SOURCE_DIR}/Dependencies/CMAKE_BUILD/_deps/argparse-src/include")
