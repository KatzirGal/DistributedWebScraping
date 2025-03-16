# === SEPARATE BUILD OUTPUT FROM CMAKE FILES ===
if (WIN32)
    set(BUILD_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/x64")
else()
    set(BUILD_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/build")
endif()

# Set output directories for binaries and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/lib)

# Also, set these per configuration to handle different build types
foreach(OUTPUT_CONFIG Debug Release RelWithDebInfo MinSizeRel)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ${BUILD_OUTPUT_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ${BUILD_OUTPUT_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ${BUILD_OUTPUT_DIR}/lib)
endforeach()

# Set Boost installation directory (Handling both single-config and multi-config generators)
set(BOOST_INSTALL_DIR "${CMAKE_SOURCE_DIR}/CMAKE_BUILD/install/${CMAKE_BUILD_TYPE}")

# Ensure CMake looks for Boost in the correct location
set(Boost_NO_SYSTEM_PATHS TRUE)  # Avoid searching system paths
set(Boost_ROOT ${BOOST_INSTALL_DIR})  # Use Boost_ROOT instead of CMAKE_PREFIX_PATH

# Use FindBoost.cmake instead of BoostConfig.cmake
find_package(Boost REQUIRED COMPONENTS system thread regex)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found in ${BOOST_INSTALL_DIR}. Make sure Boost is built and installed.")
endif()

# Set Boost include and library directories for subprojects
set(Boost_INCLUDE_DIRS ${BOOST_INSTALL_DIR}/include CACHE INTERNAL "Boost include directories")
set(Boost_LIBRARY_DIRS ${BOOST_INSTALL_DIR}/lib CACHE INTERNAL "Boost library directories")
