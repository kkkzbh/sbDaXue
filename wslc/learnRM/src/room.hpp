#pragma once

// 聊天房间管理
// 管理所有在线用户，处理消息广播

#include <boost/asio/awaitable.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/post.hpp>

#include <memory>
#include <string>
#include <unordered_set>
#include <mutex>
#include <print>

#include "protocol.hpp"
#include "redis_cache.hpp"
#include "session.hpp"

namespace chat {

namespace asio = boost::asio;

class Room : public std::enable_shared_from_this<Room> {
public:
    explicit Room(asio::io_context& ioc, std::shared_ptr<RedisCache> cache, std::size_t history_count)
        : ioc_{ioc}
        , cache_{std::move(cache)}
        , history_count_{history_count}
    {}

    // 用户加入房间
    asio::awaitable<void> join(std::shared_ptr<Session> session, const std::string& name) {
        {
            std::lock_guard lock{mutex_};
            sessions_.insert(session);
        }

        std::println("[Room] {} joined, total users: {}", name, sessions_.size());

        // 发送确认
        session->deliver(protocol::Formatter::ok_joined(name));

        // 获取并推送历史消息
        try {
            auto messages = co_await cache_->get_recent_messages(history_count_);
            
            if (!messages.empty()) {
                session->deliver(protocol::Formatter::history_start(messages.size()));
                for (const auto& msg : messages) {
                    session->deliver(msg.format());
                }
            }
        } catch (const std::exception& e) {
            std::println("[Room] Failed to get history: {}", e.what());
        }

        // 广播系统消息：用户加入
        broadcast_system(protocol::Formatter::sys_joined(name), session);
    }

    // 用户离开房间
    void leave(std::shared_ptr<Session> session) {
        std::string name;
        {
            std::lock_guard lock{mutex_};
            sessions_.erase(session);
            name = session->name();
        }

        if (!name.empty()) {
            std::println("[Room] {} left, total users: {}", name, sessions_.size());
            // 广播系统消息：用户离开
            broadcast_system(protocol::Formatter::sys_left(name), nullptr);
        }
    }

    // 广播消息
    asio::awaitable<void> broadcast_message(
        std::shared_ptr<Session> sender, 
        const std::string& content
    ) {
        // 创建消息
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        std::tm tm_buf;
        localtime_r(&time_t, &tm_buf);
        char time_str[20];
        std::strftime(time_str, sizeof(time_str), "%H:%M:%S", &tm_buf);

        protocol::ChatMessage msg{
            .sender = sender->name(),
            .content = content,
            .timestamp = time_str
        };

        // 缓存到 Redis
        try {
            co_await cache_->push_message(msg);
        } catch (const std::exception& e) {
            std::println("[Room] Failed to cache message: {}", e.what());
        }

        // 格式化协议消息
        std::string formatted = msg.format();

        // 广播给所有用户
        std::lock_guard lock{mutex_};
        for (auto& session : sessions_) {
            session->deliver(formatted);
        }
    }

    // 获取 Redis 缓存 (供 DB Worker 使用)
    [[nodiscard]] std::shared_ptr<RedisCache> cache() const { return cache_; }

private:
    // 广播系统消息 (排除指定会话)
    void broadcast_system(const std::string& msg, std::shared_ptr<Session> exclude) {
        std::lock_guard lock{mutex_};
        for (auto& session : sessions_) {
            if (session != exclude) {
                session->deliver(msg);
            }
        }
    }

    asio::io_context& ioc_;
    std::shared_ptr<RedisCache> cache_;
    std::size_t history_count_;
    std::unordered_set<std::shared_ptr<Session>> sessions_;
    std::mutex mutex_;
};

// Session 方法实现 (需要 Room 的完整定义)

inline void Session::leave_room() {
    if (joined_ && room_) {
        room_->leave(shared_from_this());
        joined_ = false;
    }
}

inline asio::awaitable<void> Session::handle_command(const std::string& line) {
    auto cmd = protocol::Parser::parse(line);

    if (auto* join = std::get_if<protocol::JoinCmd>(&cmd)) {
        if (joined_) {
            deliver(protocol::Formatter::err(1, "Already joined"));
            co_return;
        }
        name_ = join->name;
        joined_ = true;
        co_await room_->join(shared_from_this(), name_);
    }
    else if (auto* msg = std::get_if<protocol::MsgCmd>(&cmd)) {
        if (!joined_) {
            deliver(protocol::Formatter::err(2, "Not joined yet, use JOIN <name>"));
            co_return;
        }
        co_await room_->broadcast_message(shared_from_this(), msg->content);
    }
    else if (std::holds_alternative<protocol::QuitCmd>(cmd)) {
        deliver(protocol::Formatter::ok_quit());
        socket_.close();
    }
    else if (auto* invalid = std::get_if<protocol::InvalidCmd>(&cmd)) {
        deliver(protocol::Formatter::err(0, invalid->reason));
    }
}

}  // namespace chat
