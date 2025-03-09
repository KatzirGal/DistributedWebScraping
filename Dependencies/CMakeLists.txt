cmake_minimum_required(VERSION 3.20)
project(Dependencies)

# Add each dependency as a subdirectory
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Poco)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/argparse)

message(STATUS "All dependencies are now available.")
