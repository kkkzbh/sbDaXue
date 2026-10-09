

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <utility>
#include <thread>
#include <ranges>
#include <string_view>
#include <filesystem>
#include <fstream>

import utils;
import net;
import log;

using namespace std::views;
using namespace std::string_view_literals;

auto main() -> int
{
    auto const server_sock = socket(PF_INET,SOCK_STREAM,0);
    std::ignore = bind(server_sock,server_addr,server_addrsz);
    listen(server_sock,20);
    while(true) {
        auto client_addr = sockaddr_in{};
        auto client_addrsz = socklen_t{ sizeof client_addr };
        auto const client_sock = accept(server_sock,reinterpret_cast<sockaddr*>(&client_addr),&client_addrsz);
        log::write("Connection Request : {}:{}",inet_ntoa(client_addr.sin_addr),ton(client_addr.sin_port));
        std::thread {
            [client_sock] {
                auto buf = std::array<char,BUF_SIZE>{};
                auto const sz = read(client_sock,buf.data(),buf.size());
                auto sv = std::string_view(buf.data(),sz);
                auto v = sv | split("\r\n"sv);
                auto it = v.begin();
                auto request = std::string_view{ *it++ };
                if(not request.contains("HTTP/"sv)) {
                    log::error("Invalid Request!");
                    close(client_sock);
                    return;
                }
                auto req = request | split(" "sv);
                auto reqit = req.begin();
                auto method = std::string_view{ *reqit++ };
                if(method != "GET"sv) {
                    log::error("Invalid Method!");
                    close(client_sock);
                    return;
                }
                auto file = std::string_view{ *reqit++ };
                auto file_path = base_root;
                file_path += file;
                auto type = [&] {
                    auto extension = file;
                    extension.remove_prefix(extension.find_last_of("."sv) + 1);
                    if(extension == "html"sv or extension == "htm"sv) {
                        return "text/html"sv;
                    }
                    return "text/plain"sv;
                }();
                auto constexpr protocol = "HTTP/1.0 200 OK\r\n"sv;
                auto constexpr server = "Server:Linux Web Server \r\n"sv;
                auto constexpr content_size = "Content-size:2048\r\n"sv;
                auto content_type = std::format("Content-type:{}\r\n\r\n",type);
                auto os = std::ifstream{ file_path };
                if(not os) {
                    log::error("Can not open send file!");
                    close(client_sock);
                    return;
                }
                write(client_sock,protocol.data(),protocol.size());
                write(client_sock,server.data(),server.size());
                write(client_sock,content_size.data(),content_size.size());
                write(client_sock,content_type.data(),content_type.size());
                while(os.getline(buf.data(),buf.size())) {
                    auto const n = os.gcount();
                    auto line = std::string_view(buf.data(),n);
                    if(line.back() == '\0') {
                        line.remove_suffix(1);
                    }
                    write(client_sock,line.data(),line.size());
                }
                close(client_sock);
            }
        }.detach();
    }

}