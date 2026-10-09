


#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstdlib>
#include <print>
#include <iostream>
#include <string>
#include <thread>

import log;
import utils;
import net;

using namespace std::string_view_literals;
using namespace std::string_literals;

auto main() -> int
{
    std::print("login:> ");
    auto name = ""s;
    std::getline(std::cin,name);
    std::println("login successful!");
    std::println("connexcting .....");
    auto const sock = socket(PF_INET,SOCK_STREAM,0);
    std::ignore = connect(sock,server_addr,server_addrsz);
    std::println("{}connected successful!",get_time());
    auto send = std::thread {
        [sock,name = "["s + name + "]: "s] mutable {
            auto const n = name.size();
            name.resize(n + BUF_SIZE);
            auto msg = std::span<char,BUF_SIZE>{ name.data() + n,BUF_SIZE };
            while(true) {
                std::cin.getline(msg.data(),msg.size());
                auto sv = std::string_view{ msg.data(),static_cast<std::size_t>(std::cin.gcount()) };
                if(sv.back() == '\0') {
                    sv.remove_suffix(1);
                }
                if(sv == "q"sv or sv == "exit"sv) {
                    close(sock);
                    return 0;
                }
                write(sock,name.data(),n + sv.size());
            }
        }
    };

    auto recv = std::thread {
        [sock] mutable {
            auto msg = std::array<char,BUF_SIZE>{};
            while(true) {
                auto const sz = read(sock,msg.data(),msg.size());
                if(sz == -1) {
                    return -1;
                }
                auto sv = std::string_view{ msg.data(),static_cast<std::size_t>(sz) };
                std::println("{}",sv);
            }
        }
    };

    send.join();
    recv.join();

    close(sock);
}