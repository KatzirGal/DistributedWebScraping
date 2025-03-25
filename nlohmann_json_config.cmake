include(FetchContent)

# Define source and binary directories
set(NLOHMANN_JSON_SOURCE_DIR "${CMAKE_SOURCE_DIR}/Dependencies/nlohmann_json/src")
set(NLOHMANN_JSON_BINARY_DIR "${CMAKE_SOURCE_DIR}/Dependencies/nlohmann_json/CMakeBUILD")

# Declare the dependency
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
    SOURCE_DIR ${NLOHMANN_JSON_SOURCE_DIR}
    BINARY_DIR ${NLOHMANN_JSON_BINARY_DIR}
)

# Make the target available (nlohmann_json::nlohmann_json)
FetchContent_MakeAvailable(nlohmann_json)

# Optional: message to confirm setup
message(STATUS "nlohmann_json configured from ${NLOHMANN_JSON_SOURCE_DIR}")
