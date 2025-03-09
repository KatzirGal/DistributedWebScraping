project(Orchestrator)

add_executable(Orchestrator src/orchestrator.cpp)

target_link_libraries(Orchestrator PRIVATE Common)
