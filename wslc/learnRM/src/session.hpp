#pragma once

// 客户端会话管理
// 管理单个 TCP 连接的生命周期

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/steady_timer.hpp>

#include <memory>
#include <string>
#include <deque>
#include <print>
#include <functional>

#include "protocol.hpp"

namespace chat {

namespace asio = boost::asio;
using tcp = asio::ip::tcp;

// 前向声明
class Room;

class Session : public std::enable_shared_from_this<Session> {
public:
    using Ptr = std::shared_ptr<Session>;

    Session(tcp::socket socket, std::shared_ptr<Room> room)
        : socket_{std::move(socket)}
        , room_{std::move(room)}
    {
        auto endpoint = socket_.remote_endpoint();
        std::println("[Session] New connection from {}:{}", 
            endpoint.address().to_string(), endpoint.port());
    }

    ~Session() {
        std::println("[Session] {} disconnected", 
            name_.empty() ? "(unnamed)" : name_);
    }

    // 启动会话
    void start() {
        asio::co_spawn(socket_.get_executor(),
            [self = shared_from_this()] { return self->run(); },
            asio::detached);
    }

    // 发送消息到客户端
    void deliver(const std::string& msg) {
        bool writing = !write_queue_.empty();
        write_queue_.push_back(msg);
        
        if (!writing) {
            asio::co_spawn(socket_.get_executor(),
                [self = shared_from_this()] { return self->do_write(); },
                asio::detached);
        }
    }

    [[nodiscard]] const std::string& name() const { return name_; }
    [[nodiscard]] bool is_joined() const { return joined_; }

private:
    // 主运行循环
    asio::awaitable<void> run() {
        try {
            asio::streambuf buffer;
            
            while (socket_.is_open()) {
                // 读取一行
                auto bytes = co_await asio::async_read_until(
                    socket_, buffer, '\n', asio::use_awaitable);
                
                // 提取行内容
                std::istream is(&buffer);
                std::string line;
                std::getline(is, line);

                // 解析并处理命令
                co_await handle_command(line);
            }
        } catch (const boost::system::system_error& e) {
            if (e.code() != asio::error::eof && 
                e.code() != asio::error::connection_reset &&
                e.code() != asio::error::operation_aborted) {
                std::println("[Session] Error: {}", e.what());
            }
        }

        // 离开房间
        leave_room();
    }

    // 处理命令
    asio::awaitable<void> handle_command(const std::string& line);

    // 写入队列
    asio::awaitable<void> do_write() {
        try {
            while (!write_queue_.empty()) {
                auto& msg = write_queue_.front();
                co_await asio::async_write(socket_, 
                    asio::buffer(msg), asio::use_awaitable);
                write_queue_.pop_front();
            }
        } catch (const std::exception& e) {
            std::println("[Session] Write error: {}", e.what());
            socket_.close();
        }
    }

    // 离开房间 (在 room.hpp 中实现)
    void leave_room();

    tcp::socket socket_;
    std::shared_ptr<Room> room_;
    std::string name_;
    bool joined_{false};
    std::deque<std::string> write_queue_;
};

}  // namespace chat
