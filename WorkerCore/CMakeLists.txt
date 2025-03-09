project(WorkerCore)

include(${CMAKE_CURRENT_SOURCE_DIR}/file_list.cmake)

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

set(POCO_INSTALL_DIR ${CMAKE_SOURCE_DIR}/Dependencies/CMAKE_BUILD/install)

# Tell CMake to search Poco in this directory
set(CMAKE_PREFIX_PATH ${POCO_INSTALL_DIR})

find_package(Poco REQUIRED Foundation Net Util JSON XML PATHS ${POCO_INSTALL_DIR} NO_DEFAULT_PATH)

if(NOT Poco_FOUND)
    message(FATAL_ERROR "Poco not found in ${POCO_INSTALL_DIR}. Build it first using Dependencies.")
endif()

# --- Define Poco Libraries ---
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

add_poco_library(Foundation Foundation)
add_poco_library(Net Net)
if(UNIX)
    add_poco_library(NetSSL NetSSL)
endif()
add_poco_library(Util Util)
add_poco_library(JSON JSON)
add_poco_library(XML XML)

add_library(WorkerCore STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

# Include Poco headers
target_include_directories(WorkerCore PRIVATE
    ${POCO_INSTALL_DIR}/${CMAKE_BUILD_TYPE}/include
    ${WEB_SERVICE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Dependencies/CMAKE_BUILD/_deps/argparse-src/include
)

# Link Poco Libraries
target_link_libraries(
    WorkerCore 
    WebService
    Common
    Poco::Foundation
    Poco::Net
    $<$<PLATFORM_ID:Unix>:Poco::NetSSL>
    Poco::Util
    Poco::JSON
    Poco::XML
)

add_custom_command(TARGET WorkerCore POST_BUILD
    # === Foundation ===
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:${POCO_INSTALL_DIR}/Debug/bin/PocoFoundationd.dll>
    $<$<AND:$<PLATFORM_ID:Windows>,$<NOT:$<CONFIG:Debug>>>:${POCO_INSTALL_DIR}/$<CONFIG>/bin/PocoFoundation.dll>
    $<$<NOT:$<PLATFORM_ID:Windows>>:${POCO_INSTALL_DIR}/$<CONFIG>/lib/libPocoFoundation.so>
    $<TARGET_FILE_DIR:WorkerCore>

    # === Net ===
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:${POCO_INSTALL_DIR}/Debug/bin/PocoNetd.dll>
    $<$<AND:$<PLATFORM_ID:Windows>,$<NOT:$<CONFIG:Debug>>>:${POCO_INSTALL_DIR}/$<CONFIG>/bin/PocoNet.dll>
    $<$<NOT:$<PLATFORM_ID:Windows>>:${POCO_INSTALL_DIR}/$<CONFIG>/lib/libPocoNet.so>
    $<TARGET_FILE_DIR:WorkerCore>

    # === Util ===
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:${POCO_INSTALL_DIR}/Debug/bin/PocoUtild.dll>
    $<$<AND:$<PLATFORM_ID:Windows>,$<NOT:$<CONFIG:Debug>>>:${POCO_INSTALL_DIR}/$<CONFIG>/bin/PocoUtil.dll>
    $<$<NOT:$<PLATFORM_ID:Windows>>:${POCO_INSTALL_DIR}/$<CONFIG>/lib/libPocoUtil.so>
    $<TARGET_FILE_DIR:WorkerCore>

    # === JSON ===
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:${POCO_INSTALL_DIR}/Debug/bin/PocoJSONd.dll>
    $<$<AND:$<PLATFORM_ID:Windows>,$<NOT:$<CONFIG:Debug>>>:${POCO_INSTALL_DIR}/$<CONFIG>/bin/PocoJSON.dll>
    $<$<NOT:$<PLATFORM_ID:Windows>>:${POCO_INSTALL_DIR}/$<CONFIG>/lib/libPocoJSON.so>
    $<TARGET_FILE_DIR:WorkerCore>

    # === XML ===
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:${POCO_INSTALL_DIR}/Debug/bin/PocoXMLd.dll>
    $<$<AND:$<PLATFORM_ID:Windows>,$<NOT:$<CONFIG:Debug>>>:${POCO_INSTALL_DIR}/$<CONFIG>/bin/PocoXML.dll>
    $<$<NOT:$<PLATFORM_ID:Windows>>:${POCO_INSTALL_DIR}/$<CONFIG>/lib/libPocoXML.so>
    $<TARGET_FILE_DIR:WorkerCore>
)

if(UNIX)
    add_custom_command(TARGET WorkerCore POST_BUILD
        # === NetSSL ===
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${POCO_INSTALL_DIR}/$<CONFIG>/lib/libPocoNetSSL.so
            $<TARGET_FILE_DIR:WorkerCore>
    )
endif()


target_include_directories(WorkerCore PUBLIC include)
