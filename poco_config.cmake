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

# Set Poco installation directory (if applicable)
set(POCO_INSTALL_DIR ${CMAKE_SOURCE_DIR}/Dependencies/Poco/CMAKE_BUILD/install)
set(CMAKE_PREFIX_PATH ${POCO_INSTALL_DIR})

find_package(Poco REQUIRED Foundation Net Util JSON XML PATHS ${POCO_INSTALL_DIR} NO_DEFAULT_PATH)

if(NOT Poco_FOUND)
    message(FATAL_ERROR "Poco not found in ${POCO_INSTALL_DIR}. Build it first using Dependencies.")
endif()

# Function to add Poco libraries
macro(add_poco_library LIB_NAME LIB_FILE)
    if(WIN32)
        set_target_properties(Poco::${LIB_NAME} PROPERTIES
            IMPORTED_IMPLIB_DEBUG ${POCO_INSTALL_DIR}/Debug/lib/Poco${LIB_FILE}d.lib
            IMPORTED_IMPLIB_RELEASE ${POCO_INSTALL_DIR}/Release/lib/Poco${LIB_FILE}.lib
            IMPORTED_LOCATION_DEBUG ${POCO_INSTALL_DIR}/Debug/bin/Poco${LIB_FILE}d.dll
            IMPORTED_LOCATION_RELEASE ${POCO_INSTALL_DIR}/Release/bin/Poco${LIB_FILE}.dll
            IMPORTED_LOCATION_RELWITHDEBINFO ${POCO_INSTALL_DIR}/RelWithDebInfo/bin/Poco${LIB_FILE}.dll
            IMPORTED_IMPLIB_RELWITHDEBINFO ${POCO_INSTALL_DIR}/RelWithDebInfo/lib/Poco${LIB_FILE}.lib
        )
    else()
        set_target_properties(Poco::${LIB_NAME} PROPERTIES
            IMPORTED_LOCATION ${POCO_INSTALL_DIR}/${CMAKE_BUILD_TYPE}/lib/libPoco${LIB_FILE}.so
        )
    endif()
endmacro()

# Common Poco Libraries
add_poco_library(Foundation Foundation)
add_poco_library(Net Net)
add_poco_library(NetSSL NetSSL)
add_poco_library(Util Util)
add_poco_library(JSON JSON)
add_poco_library(XML XML)
