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

# Set Boost installation directory explicitly
if(CMAKE_CONFIGURATION_TYPES)  # Multi-config generators (e.g., Visual Studio)
    set(BOOST_INSTALL_DIR "${CMAKE_SOURCE_DIR}/Dependencies/boost/CMAKE_BUILD/install/Debug") # Manually setting Debug for now
else()
    set(BOOST_INSTALL_DIR "${CMAKE_SOURCE_DIR}/Dependencies/boost/CMAKE_BUILD/install/${CMAKE_BUILD_TYPE}")
endif()

# Debugging output
message(STATUS "Boost installation directory: ${BOOST_INSTALL_DIR}")

# Set Boost_DIR manually
set(Boost_DIR "${BOOST_INSTALL_DIR}/lib/cmake/Boost-1.83.0")
message(STATUS "Boost_DIR set to: ${Boost_DIR}")

# Ensure CMake searches only in the correct Boost directory
find_package(Boost REQUIRED CONFIG COMPONENTS system thread regex PATHS ${Boost_DIR} NO_DEFAULT_PATH)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found in ${Boost_DIR}. Ensure Boost is built and installed correctly.")
endif()

# Cache Boost directories for subprojects
set(Boost_INCLUDE_DIRS "${BOOST_INSTALL_DIR}/include" CACHE INTERNAL "Boost include directories")
set(Boost_LIBRARY_DIRS "${BOOST_INSTALL_DIR}/lib" CACHE INTERNAL "Boost library directories")
