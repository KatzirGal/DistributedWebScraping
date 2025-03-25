cmake_minimum_required(VERSION 3.27)
project(RestServer)

# Load source/header file list
include(${CMAKE_CURRENT_SOURCE_DIR}/file_list.cmake)

# Boost setup
include(${CMAKE_SOURCE_DIR}/boost_config.cmake)

add_library(RestServer STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

target_include_directories(RestServer
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/Common/include
    PRIVATE
        ${Boost_INCLUDE_DIRS}
)


target_link_libraries(RestServer PUBLIC ${Boost_LIBRARIES})
