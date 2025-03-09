cmake_minimum_required(VERSION 3.20)
project(argparseDependency)

include(FetchContent)

set(ARGPARSE_SOURCE_DIR ${CMAKE_BINARY_DIR}/Dependencies/argparse/src)
set(ARGPARSE_BINARY_DIR ${CMAKE_BINARY_DIR}/Dependencies/argparse/CMakeBUILD)

FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
    GIT_TAG v2.9
    SOURCE_DIR ${ARGPARSE_SOURCE_DIR}
    BINARY_DIR ${ARGPARSE_BINARY_DIR}
)

FetchContent_MakeAvailable(argparse)

