project(WorkerNode)

# === SEPARATE BUILD OUTPUT FROM CMAKE FILES ===
if (WIN32)
    set(BUILD_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/x64")
else()
    set(BUILD_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/build")
endif()

# Set output directories for binaries and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/lib)

# Also, set these per configuration to handle different build types
foreach(OUTPUT_CONFIG Debug Release RelWithDebInfo MinSizeRel)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ${BUILD_OUTPUT_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ${BUILD_OUTPUT_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ${BUILD_OUTPUT_DIR}/lib)
endforeach()

add_executable(WorkerNode src/worker_node.cpp)
target_link_libraries(WorkerNode PRIVATE WorkerCore)

add_custom_command(TARGET WorkerNode POST_BUILD
    # Copy DLLs (ensures correct Debug/Release versions)
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/PocoFoundation$<$<CONFIG:Debug>:d>.dll
        ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/PocoJSON$<$<CONFIG:Debug>:d>.dll
        ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/PocoNet$<$<CONFIG:Debug>:d>.dll
        ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/PocoUtil$<$<CONFIG:Debug>:d>.dll
        ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/PocoXML$<$<CONFIG:Debug>:d>.dll
        $<TARGET_FILE_DIR:WorkerNode>

    # Copy WorkerCore.lib (needed for linking)
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/WorkerCore.lib
        $<TARGET_FILE_DIR:WorkerNode>

    # Copy WorkerCore.pdb (only needed for debugging)
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${BUILD_OUTPUT_DIR}/lib/$<CONFIG>/WorkerCore.pdb
        $<TARGET_FILE_DIR:WorkerNode>
)
