#include <iostream>
#include <vector>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main() {
    try {
        // 创建IO服务对象
        boost::asio::io_service io_service;

        // 解析服务器地址和端口
        tcp::resolver resolver(io_service);
        tcp::resolver::query query("127.0.0.1", "12345");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        // 创建并连接到服务器
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        std::cout << "Connected to server. Listening for messages..." << std::endl;

        while (true) {
            // 接收来自服务器的消息
            std::vector<char> buf(128);
            boost::system::error_code error;
            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            if (error == boost::asio::error::eof) {
                // 连接关闭
                std::cout << "Connection closed by server." << std::endl;
                break;
            } else if (error) {
                throw boost::system::system_error(error); // 其他错误
            }

            std::cout << "Received message from server: ";
            std::cout.write(buf.data(), len);
            std::cout << std::endl;
        }

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
