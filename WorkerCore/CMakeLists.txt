project(WorkerCore)

add_library(WorkerCore STATIC
    src/worker_core.cpp
)

target_include_directories(WorkerCore PUBLIC include)
target_link_libraries(WorkerCore PRIVATE Common)
