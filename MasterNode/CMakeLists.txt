project(master_node)

add_executable(master_node src/main.cpp)
target_link_libraries(master_node PRIVATE master_core)
