#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main() {
    try {
        // 创建IO服务对象
        boost::asio::io_service io_service;

        // 创建并打开接收端口
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 12345));

        std::cout << "Server is running on port 12345..." << std::endl;

        for (;;) {
            // 创建一个socket对象
            tcp::socket socket(io_service);

            // 等待客户端连接
            acceptor.accept(socket);

            // 向客户端发送消息
            std::string message = "Hello from server";
            boost::asio::write(socket, boost::asio::buffer(message));

            std::cout << "Sent message to client: " << message << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
