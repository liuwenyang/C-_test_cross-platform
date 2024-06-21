# CMakeLists.txt

# 设置最低CMake版本要求
cmake_minimum_required(VERSION 3.10)

# 定义项目名称和使用的C++标准
project(MyShellProject VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加myshell库
add_library(myshell STATIC myshell/myshell.cpp myshell/myshell.h)

# 添加可执行文件
add_executable(MyShell main.cpp)

# 链接myshell库
target_link_libraries(MyShell PRIVATE myshell)
