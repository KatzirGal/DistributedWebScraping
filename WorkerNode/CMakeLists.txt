project(WorkerNode)

add_executable(WorkerNode src/worker_node.cpp)
target_link_libraries(WorkerNode PRIVATE WorkerCore)
