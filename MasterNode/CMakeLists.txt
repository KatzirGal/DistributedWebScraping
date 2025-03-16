cmake_minimum_required(VERSION 3.27)
project(MasterNode)

add_executable(MasterNode src/master_node.cpp)
target_link_libraries(MasterNode PRIVATE MasterCore)
