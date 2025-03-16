cmake_minimum_required(VERSION 3.27)
project(MasterCore)

add_library(MasterCore STATIC
    src/master_core.cpp
)

target_include_directories(MasterCore PUBLIC include)
target_link_libraries(MasterCore PRIVATE Common)
