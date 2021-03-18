cmake_minimum_required(VERSION 3.18)
project(server)

set(CMAKE_CXX_STANDARD 14)

# 添加 math 子目录
add_subdirectory(buffer)

add_executable(server main.cpp)

# 添加链接库
target_link_libraries(server Buffer)