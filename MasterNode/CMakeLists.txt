project(MasterNode)

add_executable(MasterNode src/master_node.cpp)
target_link_libraries(MasterNode PRIVATE MasterCore)
