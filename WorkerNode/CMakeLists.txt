project(WorkerNode)

add_executable(WorkerNode src/WorkerNode.cpp)
target_link_libraries(WorkerNode PRIVATE WorkerCore)

add_custom_command(TARGET WorkerNode POST_BUILD
    # COMMAND ${CMAKE_COMMAND} -E copy_if_different
    #     ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/PocoFoundation$<$<CONFIG:Debug>:d>.dll
    #     ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/PocoJSON$<$<CONFIG:Debug>:d>.dll
    #     ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/PocoNet$<$<CONFIG:Debug>:d>.dll
    #     ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/PocoUtil$<$<CONFIG:Debug>:d>.dll
    #     ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/PocoXML$<$<CONFIG:Debug>:d>.dll
    #     $<TARGET_FILE_DIR:WorkerNode>

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/WorkerCore.lib
        $<TARGET_FILE_DIR:WorkerNode>

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/WorkerCore.pdb
        $<TARGET_FILE_DIR:WorkerNode>
)

target_include_directories(WorkerNode PUBLIC
    include
)