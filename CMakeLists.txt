cmake_minimum_required(VERSION 3.20)
project(DistributedWebScraping)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define directories
set(COMMON_DIR ${CMAKE_SOURCE_DIR}/Common)
set(MASTER_CORE_DIR ${CMAKE_SOURCE_DIR}/MasterCore)
set(WORKER_CORE_DIR ${CMAKE_SOURCE_DIR}/WorkerCore)
set(MASTER_DIR ${CMAKE_SOURCE_DIR}/MasterNode)
set(WORKER_DIR ${CMAKE_SOURCE_DIR}/WorkerNode)
set(ORCHESTRATOR_DIR ${CMAKE_SOURCE_DIR}/Orchestrator)

# Add subprojects
add_subdirectory(${COMMON_DIR})
add_subdirectory(${MASTER_CORE_DIR})
add_subdirectory(${WORKER_CORE_DIR})
add_subdirectory(${MASTER_DIR})
add_subdirectory(${WORKER_DIR})
add_subdirectory(${ORCHESTRATOR_DIR})
