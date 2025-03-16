project(Common)

include(${CMAKE_CURRENT_SOURCE_DIR}/file_list.cmake)

add_library(Common STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

target_include_directories(Common PRIVATE
    ${POCO_INSTALL_DIR}/${CMAKE_BUILD_TYPE}/include
)

target_include_directories(Common PUBLIC 
    include
)

target_link_libraries( Common
    
)

