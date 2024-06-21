#include <iostream>   // 包含输入输出流头文件，用于打印输出
#include <string>     // 包含字符串处理的头文件
#include <curl/curl.h> // 包含libcurl库的头文件

// 这个函数是libcurl的回调函数，用于处理接收到的数据
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    // 将接收到的数据追加到用户提供的string对象中
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    // 返回处理的数据大小，libcurl用这个值判断数据是否处理完毕
    return size * nmemb;
}

int main() {
    // 初始化一个CURL类型的指针，用于后续的HTTP请求
    CURL* curl;
    // 存储CURL的返回码，用于判断请求是否成功
    CURLcode res;

    // 用于存储响应数据的字符串
    std::string readBuffer;

    // 调用curl_global_init()来初始化libcurl库，设置默认选项
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // 获取一个易于处理的CURL句柄
    curl = curl_easy_init();

    // 检查CURL句柄是否成功获取
    if (curl) {
        // 设置要访问的URL
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.example.com/data");

        // 设置回调函数，用于处理接收到的数据
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        // 设置用于存储接收到的数据的字符串
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // 执行请求，res将包含请求的返回码
        res = curl_easy_perform(curl);

        // 检查请求是否成功
        if (res != CURLE_OK) {
            // 如果请求失败，输出错误信息
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // 如果请求成功，输出接收到的数据
            std::cout << "Received data: " << readBuffer << std::endl;
        }

        // 释放CURL句柄，清理相关资源
        curl_easy_cleanup(curl);
    }

    // 释放libcurl库相关资源
    curl_global_cleanup();

    return 0;
}
