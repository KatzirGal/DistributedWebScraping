cmake_minimum_required(VERSION 3.27)
project(BoostDependency)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Restrict configurations for multi-config generators (e.g., Visual Studio)
if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "" FORCE)
endif()

# Set build type for single-config generators
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose build type: Debug, Release, or RelWithDebInfo" FORCE)
endif()

# FIX: Set Boost installation directory correctly (no $<CONFIG> in file paths)
if(CMAKE_CONFIGURATION_TYPES)
    set(BOOST_INSTALL_DIR "${CMAKE_SOURCE_DIR}/CMAKE_BUILD/install")
else()
    set(BOOST_INSTALL_DIR "${CMAKE_SOURCE_DIR}/CMAKE_BUILD/install/${CMAKE_BUILD_TYPE}")
endif()

# Ensure output directories exist
file(MAKE_DIRECTORY ${BOOST_INSTALL_DIR})

# Fetch Boost using ExternalProject_Add
include(ExternalProject)
ExternalProject_Add(
    Boost
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG boost-1.83.0
    PREFIX ${CMAKE_BINARY_DIR}/boost-prefix
    SOURCE_DIR ${CMAKE_BINARY_DIR}/boost-src
    BINARY_DIR ${CMAKE_BINARY_DIR}/boost-build
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    LOG_BUILD ON
)

# Ensure that Boost is fully downloaded before running bootstrap.bat
ExternalProject_Add_Step(Boost bootstrap
    COMMAND bootstrap.bat
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/boost-src
    DEPENDEES download
    DEPENDERS build
)

# Ensure Boost is installed after bootstrapping
ExternalProject_Add_Step(Boost install_boost
    COMMAND b2 install --prefix=${BOOST_INSTALL_DIR}/${CMAKE_BUILD_TYPE} --layout=system --with-system --with-thread --with-regex variant=debug address-model=64
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/boost-src
    DEPENDEES bootstrap
    DEPENDERS install
)



# Define Boost include and library directories
set(Boost_INCLUDE_DIR ${BOOST_INSTALL_DIR}/include CACHE PATH "Boost include directories")
set(Boost_LIBRARY_DIR ${BOOST_INSTALL_DIR}/lib CACHE PATH "Boost library directories")
set(Boost_FOUND TRUE CACHE BOOL "Boost found")

# Mark `Boost` target as available for dependencies
ExternalProject_Add_StepTargets(Boost build install)
