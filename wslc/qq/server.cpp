

#include<iostream>
#include<print>
#include<unistd.h>
#include<arpa/inet.h>

auto main() -> int 
{
    auto fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1) {
        perror("socket");
        return -1;
    }
    auto saddr = sockaddr_in{ AF_INET, htons(10086), INADDR_ANY };
    auto ret = bind(fd, reinterpret_cast<sockaddr*>(&saddr), sizeof(saddr));
    if(ret == -1) {
        perror("bind");
        return -1;
    }
    ret = listen(fd,10);
    if(ret == -1) {
        perror("listen");
        return -1;
    }
    auto caddr = sockaddr_in{};
    auto caddr_len = socklen_t(sizeof(caddr));
    auto cfd = accept(fd, reinterpret_cast<sockaddr*>(&caddr), &caddr_len);
    if(cfd == -1) {
        perror("accept");
        return -1;
    }
    char ip[32];
    std::println("客户端的IP {}, 端口: {}",
        inet_ntop(AF_INET,&caddr.sin_addr.s_addr,ip,sizeof(ip)),
        ntohs(caddr.sin_port));
    char buf[1024];
    while(true) {
        auto len = recv(cfd,buf,sizeof(buf),0);
        if(len > 0) {
            std::println("server reciev the information: {}",buf);
            send(cfd,buf,len,0);
        } else if(len == 0) {
            std::println("client close");
            break;
        } else {
            perror("recv");
            break;
        }
    }
    close(fd);
    close(cfd);
}
