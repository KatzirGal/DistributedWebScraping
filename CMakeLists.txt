cmake_minimum_required(VERSION 3.16)
project(DWS)

# Enable C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define directories
set(COMMON_DIR ${CMAKE_SOURCE_DIR}/common)
set(MASTER_CORE_DIR ${CMAKE_SOURCE_DIR}/master_core)
set(WORKER_CORE_DIR ${CMAKE_SOURCE_DIR}/worker_core)
set(MASTER_DIR ${CMAKE_SOURCE_DIR}/master_node)
set(WORKER_DIR ${CMAKE_SOURCE_DIR}/worker_node)
set(ORCHESTRATOR_DIR ${CMAKE_SOURCE_DIR}/orchestrator)

# Add subprojects
add_subdirectory(${COMMON_DIR})
add_subdirectory(${MASTER_CORE_DIR})
add_subdirectory(${WORKER_CORE_DIR})
add_subdirectory(${MASTER_DIR})
add_subdirectory(${WORKER_DIR})
add_subdirectory(${ORCHESTRATOR_DIR})
