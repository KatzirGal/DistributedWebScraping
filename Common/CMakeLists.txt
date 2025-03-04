project(common)

add_library(common STATIC
    src/networking.cpp
    src/logging.cpp
)

target_include_directories(common PUBLIC include)
