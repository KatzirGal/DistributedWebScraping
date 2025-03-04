project(worker_core)

add_library(worker_core STATIC
    src/worker_core.cpp
)

target_include_directories(worker_core PUBLIC include)
target_link_libraries(worker_core PRIVATE common)
