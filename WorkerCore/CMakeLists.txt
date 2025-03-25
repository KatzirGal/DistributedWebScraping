cmake_minimum_required(VERSION 3.18)
project(WorkerCore)

include(${CMAKE_CURRENT_SOURCE_DIR}/file_list.cmake)

add_library(WorkerCore STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

include(${CMAKE_SOURCE_DIR}/boost_config.cmake)
include(${CMAKE_SOURCE_DIR}/nlohmann_json_config.cmake)

# Include directories
target_include_directories(WorkerCore
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${Boost_INCLUDE_DIRS}
        ${WEB_SERVICE_DIR}/include
        ${CMAKE_SOURCE_DIR}/Dependencies/argparse/CMAKE_BUILD/Dependencies/argparse/src/include
        ${CMAKE_SOURCE_DIR}/RestServer/include
)

# Link dependencies
target_link_libraries(WorkerCore
    PRIVATE
        RestServer
        Common
        Boost::system
        Boost::thread
        Boost::regex
        nlohmann_json::nlohmann_json
)

