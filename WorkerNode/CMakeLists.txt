cmake_minimum_required(VERSION 3.27)
project(WorkerNode)

add_executable(WorkerNode src/WorkerNode.cpp)
target_link_libraries(WorkerNode PRIVATE WorkerCore)

# add_custom_command(TARGET WorkerNode POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/WorkerCore.lib
#         $<TARGET_FILE_DIR:WorkerNode>

#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/WorkerCore.pdb
#         $<TARGET_FILE_DIR:WorkerNode>
# )

target_include_directories(WorkerNode 
    PUBLIC
        include
    PRIVATE
        ${Boost_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/RestServer/include
)

target_link_libraries(WorkerNode
    PRIVATE
        WorkerCore
        Common
        nlohmann_json::nlohmann_json
        crypt32
)
