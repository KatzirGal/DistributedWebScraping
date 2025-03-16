project(Common)

include(${CMAKE_CURRENT_SOURCE_DIR}/file_list.cmake)

add_library(Common STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

# Find Boost components that require linking
find_package(Boost REQUIRED COMPONENTS system)

# Include Boost headers manually (Beast & Asio are header-only)
target_include_directories(Common PUBLIC 
    include
    ${Boost_INCLUDE_DIRS}
)

# Link necessary Boost libraries
target_link_libraries(Common PUBLIC
    Boost::system
)
