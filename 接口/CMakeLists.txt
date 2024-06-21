cmake_minimum_required(VERSION 3.10)
project(NetworkExample VERSION 1.0)

# 查找Boost库
find_package(Boost 1.65 REQUIRED COMPONENTS system)

# 包含Boost头文件
include_directories(${Boost_INCLUDE_DIRS})

# 添加可执行文件
add_executable(server server.cpp)
add_executable(client client.cpp)

# 链接Boost库和pthread库
target_link_libraries(server ${Boost_LIBRARIES} pthread)
target_link_libraries(client ${Boost_LIBRARIES} pthread)

# 设置目标系统架构
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64" OR CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv8-a")
endif()

# 设置跨平台编译选项
if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
endif()
