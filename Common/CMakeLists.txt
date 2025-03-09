project(Common)

add_library(Common STATIC
    src/networking.cpp
    src/logging.cpp
)

target_include_directories(Common PUBLIC include)
