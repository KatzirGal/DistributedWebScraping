project(WorkerCore)

include(${CMAKE_CURRENT_SOURCE_DIR}/file_list.cmake)

add_library(WorkerCore STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

target_include_directories(WorkerCore PRIVATE
    ${POCO_INSTALL_DIR}/${CMAKE_BUILD_TYPE}/include
    ${WEB_SERVICE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Dependencies/argparse/CMAKE_BUILD/Dependencies/argparse/src/include
)

target_include_directories(WorkerCore PUBLIC
    include
)

target_link_libraries( WorkerCore
    RestServer
    Common
)
