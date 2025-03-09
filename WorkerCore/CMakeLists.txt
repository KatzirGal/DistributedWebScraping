project(WorkerCore)

include(${CMAKE_CURRENT_SOURCE_DIR}/file_list.cmake)

# Include the common Poco configuration
include(${CMAKE_SOURCE_DIR}/poco_config.cmake)

add_library(WorkerCore STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

# Include Poco headers
target_include_directories(WorkerCore PRIVATE
    ${POCO_INSTALL_DIR}/${CMAKE_BUILD_TYPE}/include
    ${WEB_SERVICE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Dependencies/argparse/CMAKE_BUILD/Dependencies/argparse/src/include
)

target_include_directories(WorkerCore PUBLIC
    include
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
