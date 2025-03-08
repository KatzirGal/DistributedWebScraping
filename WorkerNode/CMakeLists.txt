project(WorkerNode)

# Include the common Poco configuration
include(${CMAKE_SOURCE_DIR}/poco_config.cmake)

add_executable(WorkerNode src/WorkerNode.cpp)
target_link_libraries(WorkerNode PRIVATE WorkerCore Poco::Foundation Poco::Net Poco::Util Poco::JSON Poco::XML)

add_custom_command(TARGET WorkerNode POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/PocoFoundation$<$<CONFIG:Debug>:d>.dll
        ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/PocoJSON$<$<CONFIG:Debug>:d>.dll
        ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/PocoNet$<$<CONFIG:Debug>:d>.dll
        ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/PocoUtil$<$<CONFIG:Debug>:d>.dll
        ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/PocoXML$<$<CONFIG:Debug>:d>.dll
        $<TARGET_FILE_DIR:WorkerNode>

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