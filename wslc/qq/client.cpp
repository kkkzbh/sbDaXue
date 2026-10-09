

#include<iostream>
#include<fstream>
#include<netinet/in.h>
#include<print>
#include<unistd.h>
#include<arpa/inet.h>
#include<thread>
#include<chrono>

using namespace std::chrono_literals;

auto main() -> int 
{
    auto fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1) {
        perror("socker");
        return -1;
    }
    auto caddr = sockaddr_in{ AF_INET,htons(10086) };
    inet_pton(AF_INET,"10.91.173.196",&caddr.sin_addr.s_addr);
    auto ret = connect(fd,reinterpret_cast<sockaddr*>(&caddr),sizeof(caddr));
    if(ret == -1) {
        perror("bind");
        return -1;
    }
    auto constexpr buf_size = 1024;
    auto buf = std::string(buf_size,0);
    while(true) {
        std::print("input the information you want\n:>");
        std::cin.read(buf.data(),buf.size());
        send(fd,buf.data(),std::cin.gcount() + 1,0);
        buf.clear();
        buf.resize(buf_size);
        auto len = recv(fd,buf.data(),buf.size(),0);
        if(len > 0) {
            std::println("server say: {}",buf.data());
        } else if(len == 0) {
            std::println("server close");
            break;
        } else {
            perror("recv");
            break;
        }
        std::this_thread::sleep_for(200ms);
        buf.clear();
        buf.resize(buf_size);
        std::cin.clear();
    }
    close(fd);

}
