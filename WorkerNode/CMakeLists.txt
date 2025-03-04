project(worker_node)

add_executable(worker_node src/main.cpp)
target_link_libraries(worker_node PRIVATE worker_core)
