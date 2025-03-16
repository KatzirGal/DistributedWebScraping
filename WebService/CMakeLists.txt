project(WebService)

# Include file list
include(${CMAKE_CURRENT_SOURCE_DIR}/file_list.cmake)

add_library(WebService STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

# Include Poco headers
target_include_directories(WebService PRIVATE
    ${POCO_INSTALL_DIR}/${CMAKE_BUILD_TYPE}/include
)

target_include_directories(WebService PUBLIC
    include
)

# Link Poco Libraries
target_link_libraries(WebService 
    Common
)