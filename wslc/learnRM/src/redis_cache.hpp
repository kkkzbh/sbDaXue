#pragma once

// Redis 缓存层
// 使用 boost.redis 实现消息缓存
// 采用 LIST 结构存储最近 N 条消息

#include <boost/redis/connection.hpp>
#include <boost/redis/request.hpp>
#include <boost/redis/response.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>

#include <string>
#include <vector>
#include <memory>
#include <print>

#include "config.hpp"
#include "protocol.hpp"

namespace chat {

namespace asio = boost::asio;
namespace redis = boost::redis;

class RedisCache : public std::enable_shared_from_this<RedisCache> {
public:
    explicit RedisCache(asio::io_context& ioc, const RedisConfig& config)
        : conn_{std::make_shared<redis::connection>(ioc)}
        , config_{config}
    {}

    // 连接到 Redis
    asio::awaitable<void> connect() {
        redis::config cfg;
        cfg.addr.host = config_.host;
        cfg.addr.port = std::to_string(config_.port);
        
        co_await conn_->async_run(cfg, {}, asio::use_awaitable);
    }

    // 启动连接 (fire-and-forget)
    void start() {
        asio::co_spawn(conn_->get_executor(), 
            [self = shared_from_this()]() -> asio::awaitable<void> {
                try {
                    redis::config cfg;
                    cfg.addr.host = self->config_.host;
                    cfg.addr.port = std::to_string(self->config_.port);
                    
                    std::println("[Redis] Connecting to {}:{}", 
                        self->config_.host, self->config_.port);
                    
                    co_await self->conn_->async_run(cfg, {}, asio::use_awaitable);
                } catch (const std::exception& e) {
                    std::println("[Redis] Connection error: {}", e.what());
                }
            },
            asio::detached
        );
    }

    // 推送消息到缓存 (LPUSH + LTRIM 保持最近 N 条)
    asio::awaitable<void> push_message(const protocol::ChatMessage& msg) {
        redis::request req;
        redis::response<std::int64_t, std::string> resp;

        std::string serialized = msg.serialize();
        
        // LPUSH: 添加到列表头部
        req.push("LPUSH", config_.message_list_key, serialized);
        // LTRIM: 保留最近 N 条
        req.push("LTRIM", config_.message_list_key, "0", 
            std::to_string(config_.max_cached_messages - 1));

        co_await conn_->async_exec(req, resp, asio::use_awaitable);
        
        std::println("[Redis] Pushed message from {}", msg.sender);
    }

    // 获取最近 N 条消息
    asio::awaitable<std::vector<protocol::ChatMessage>> get_recent_messages(std::size_t count) {
        redis::request req;
        redis::response<std::vector<std::string>> resp;

        // LRANGE: 获取列表范围
        req.push("LRANGE", config_.message_list_key, "0", std::to_string(count - 1));

        co_await conn_->async_exec(req, resp, asio::use_awaitable);

        std::vector<protocol::ChatMessage> messages;
        auto& list = std::get<0>(resp).value();
        
        messages.reserve(list.size());
        for (const auto& item : list) {
            if (auto msg = protocol::ChatMessage::deserialize(item)) {
                messages.push_back(std::move(*msg));
            }
        }

        // 反转顺序，最早的消息在前
        std::ranges::reverse(messages);
        
        std::println("[Redis] Retrieved {} messages", messages.size());
        co_return messages;
    }

    // 获取所有缓存消息并清空 (用于批量入库)
    asio::awaitable<std::vector<protocol::ChatMessage>> pop_all_messages() {
        redis::request req;
        redis::response<std::vector<std::string>> resp;

        // LRANGE: 获取所有消息
        req.push("LRANGE", config_.message_list_key, "0", "-1");

        co_await conn_->async_exec(req, resp, asio::use_awaitable);

        std::vector<protocol::ChatMessage> messages;
        auto& list = std::get<0>(resp).value();
        
        if (!list.empty()) {
            // 清空列表
            redis::request del_req;
            redis::response<std::int64_t> del_resp;
            del_req.push("DEL", config_.message_list_key);
            co_await conn_->async_exec(del_req, del_resp, asio::use_awaitable);

            messages.reserve(list.size());
            for (const auto& item : list) {
                if (auto msg = protocol::ChatMessage::deserialize(item)) {
                    messages.push_back(std::move(*msg));
                }
            }
            
            // 反转顺序
            std::ranges::reverse(messages);
        }

        co_return messages;
    }

    // 取消连接
    void cancel() {
        conn_->cancel();
    }

private:
    std::shared_ptr<redis::connection> conn_;
    RedisConfig config_;
};

}  // namespace chat
