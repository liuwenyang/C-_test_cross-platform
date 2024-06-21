// main.cpp

#include <iostream>   // 用于标准输入输出
#include <thread>     // 用于多线程支持
#include <chrono>     // 用于时间控制
#include "myshell/myshell.h"  // 包含myshell头文件

int main() {
    // 无限循环，循环打印日志
    while (true) {
        MyShellInfo << "detectEngine deinit ok";

        // 等待1秒
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0; // 程序正常结束
}
