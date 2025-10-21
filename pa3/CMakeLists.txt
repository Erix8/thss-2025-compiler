cmake_minimum_required(VERSION 3.10)
project(sysy_formatter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# 包含 antlr4 runtime
add_subdirectory(third_party/antlr4-runtime)

# 头文件路径
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/antlr4-runtime/runtime/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 生成可执行文件
file(GLOB SRC_FILES
    src/*.cpp
)

add_executable(sysy_formatter ${SRC_FILES})

# 链接 runtime
target_link_libraries(sysy_formatter antlr4_shared)