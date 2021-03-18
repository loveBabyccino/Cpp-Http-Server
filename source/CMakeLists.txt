cmake_minimum_required(VERSION 3.18)
project(source)

set(CMAKE_CXX_STANDARD 14)

# 添加 math 子目录
add_subdirectory(buffer)

add_executable(source main.cpp)

# 添加链接库
target_link_libraries(source Buffer)