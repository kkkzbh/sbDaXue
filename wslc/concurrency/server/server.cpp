


#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <array>
#include <ranges>
#include <thread>
#include <mutex>
#include <functional>
#include <chrono>

import log;
import net;
import utils;

using namespace std::views;

auto main() -> int
{
    log::write("{}server is start!",get_time());
    auto const server_socket = socket(PF_INET,SOCK_STREAM,0);
    std::ignore = bind(server_socket,server_addr,server_addrsz);
    listen(server_socket,5);
    auto mtx = std::mutex{};
    auto client = std::vector<std::remove_const_t<decltype(server_socket)>>{};
    while(true) {
        auto client_addr = sockaddr_in{};
        auto client_addrsz = socklen_t{ sizeof client_addr };
        auto const client_socket = accept(server_socket,reinterpret_cast<sockaddr*>(&client_addr),&client_addrsz);
        std::invoke([&] {
            auto lgd = std::lock_guard{ mtx };
            client.emplace_back(client_socket);
        });
        std::thread {
            [&mtx,&client,client_socket] {
                auto msg = std::array<char,BUF_SIZE>{};
                while(auto const sz = read(client_socket,msg.data(),msg.size())) {
                    auto lgd = std::lock_guard{ mtx };
                    for(auto const sock : client) {
                        write(sock,msg.data(),sz);
                    }
                }
                std::invoke([&] {
                    auto lgd = std::lock_guard{ mtx };
                    client.erase(std::ranges::find(client,client_socket));
                });
                close(client_socket);
            }
        }.detach();
        log::write("{}Connected client IP: {}",get_time(),inet_ntoa(client_addr.sin_addr));
    }
    close(server_socket);
}