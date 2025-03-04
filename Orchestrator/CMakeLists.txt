project(orchestrator)

add_executable(orchestrator src/main.cpp)

target_link_libraries(orchestrator PRIVATE common)
