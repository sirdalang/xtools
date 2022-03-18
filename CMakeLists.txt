cmake_minimum_required(VERSION 3.15)

project (xtools)

set(CMAKE_CXX_STANDARD 11)

# for clangd use
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output/bin)

# add_subdirectory(xconfig)
add_subdirectory(xlog)
add_subdirectory(xconfig)