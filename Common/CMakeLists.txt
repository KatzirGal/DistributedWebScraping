cmake_minimum_required(VERSION 3.27)
project(Common)

include(${CMAKE_CURRENT_SOURCE_DIR}/file_list.cmake)

add_library(Common STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

# Find Boost components that require linking
find_package(Boost REQUIRED COMPONENTS system)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
find_package(OpenSSL REQUIRED)


# Include Boost & OpenSSL headers
target_include_directories(Common PUBLIC 
    include
    ${Boost_INCLUDE_DIRS}
    ${OPENSSL_INCLUDE_DIR}  # Add OpenSSL include directory
)

# Link necessary libraries (Boost and OpenSSL)
target_link_libraries(Common PUBLIC
    Boost::system
    OpenSSL::SSL
    OpenSSL::Crypto
)
