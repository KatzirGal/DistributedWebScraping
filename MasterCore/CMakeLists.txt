project(master_core)

add_library(master_core STATIC
    src/master_core.cpp
)

target_include_directories(master_core PUBLIC include)
target_link_libraries(master_core PRIVATE common)
