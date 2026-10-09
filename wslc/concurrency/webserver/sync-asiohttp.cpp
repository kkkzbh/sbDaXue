

#include <print>
#include <asio.hpp>
#include <string_view>
#include <string>
#include <iostream>
// #include <asio/ssl.hpp>

using namespace std::string_view_literals;
using namespace std::string_literals;

auto http_request(std::string_view server,std::string_view path) -> void;

auto handle_request(auto& socket, std::string_view server,std::string_view path) -> void;

auto http_request(std::string_view server,std::string_view path) -> void
{
    using asio::ip::tcp;
    auto io_context = asio::io_context{};
    auto resolver = tcp::resolver{ io_context };
    std::println("解析服务器: {}",server);
    auto const endpoints = resolver.resolve(server,"http"sv);
    std::println("DNS解析成功");
    auto sock = tcp::socket{ io_context };
    std::println("正在连接服务器");
    asio::connect(sock,endpoints);
    std::println("连接成功，发送请求...");
    handle_request(sock,server,path);
}

// auto https_request(std::string_view server,std::string_view path) -> void
// {
//     using asio::ip::tcp;
//     auto io_context = asio::io_context{};
//     auto ssl_context = asio::ssl::context{asio::ssl::context::sslv23};
//     ssl_context.set_default_verify_paths();
//     ssl_context.set_verify_mode(asio::ssl::verify_peer);
//     auto resolver = tcp::resolver{ io_context };
//     auto const endpoints = resolver.resolve(server,"https"sv);
//     auto sock = asio::ssl::stream<tcp::socket>{ io_context,ssl_context };
//     asio::connect(sock.lowest_layer(),endpoints);
//     sock.handshake(asio::ssl::stream_base::client);
//     handle_request(sock,server,path);
// }

auto handle_request(auto& socket, std::string_view server,std::string_view path) -> void
{
    auto request = std::format(
        "GET {} HTTP/1.1\r\n"
        "Host: {}\r\n"
        "Accept: */*\r\n"
        "Connection: close\r\n\r\n",
        path,server
    );
    std::println("发送HTTP请求:");
    std::println("{}",request);
    asio::write(socket,asio::buffer(request));
    std::println("请求已发送，等待相应...");
    auto buffer = std::array<char,1024>{};
    auto error = asio::error_code{};
    while(auto sz = socket.read_some(asio::buffer(buffer),error)) {
        std::cout.write(buffer.data(),sz);
    }
    std::println("---请求结束---");
}

auto main() -> int
{
    auto constexpr server = "www.baidu.com"sv;
    auto constexpr path = "/"sv;
    std::println("开始HTTP请求: http://{}{}",server,path);
    try {
        http_request(server,path);
        std::println("请求完成");
    } catch(std::exception& e) {
        std::println(stderr,"Exception: {}",e.what());
    }
}