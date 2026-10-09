#pragma once

// 数据库后台工作者
// 运行在独立线程池，定时批量将消息入库

#include <boost/asio/io_context.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>

#include <sqlpp23/postgresql/postgresql.h>
#include <sqlpp23/sqlpp23.h>

#include <memory>
#include <chrono>
#include <print>
#include <vector>

#include "config.hpp"
#include "protocol.hpp"
#include "redis_cache.hpp"

namespace chat {

namespace asio = boost::asio;
namespace pg = sqlpp::postgresql;

// 消息表定义 (sqlpp23 风格)
namespace db {

struct Messages {
    struct Id {
        using value_type = std::int64_t;
        static constexpr auto name = "id";
    };
    
    struct Sender {
        using value_type = std::string;
        static constexpr auto name = "sender";
    };
    
    struct Content {
        using value_type = std::string;
        static constexpr auto name = "content";
    };
    
    struct CreatedAt {
        using value_type = std::chrono::system_clock::time_point;
        static constexpr auto name = "created_at";
    };

    static constexpr auto table_name = "messages";
};

}  // namespace db

class DbWorker : public std::enable_shared_from_this<DbWorker> {
public:
    DbWorker(
        asio::io_context& db_ioc,
        std::shared_ptr<RedisCache> cache,
        const DatabaseConfig& db_config,
        const DbWorkerConfig& worker_config
    )
        : db_ioc_{db_ioc}
        , timer_{db_ioc}
        , cache_{std::move(cache)}
        , db_config_{db_config}
        , worker_config_{worker_config}
    {}

    // 启动定时任务
    void start() {
        std::println("[DbWorker] Starting with interval {}ms, batch size {}", 
            worker_config_.batch_interval_ms, worker_config_.batch_size);
        
        asio::co_spawn(db_ioc_,
            [self = shared_from_this()] { return self->run(); },
            asio::detached);
    }

    void stop() {
        running_ = false;
        timer_.cancel();
    }

private:
    asio::awaitable<void> run() {
        // 创建数据库连接
        auto conn = create_connection();
        if (!conn) {
            std::println("[DbWorker] Failed to create database connection, worker stopped");
            co_return;
        }

        running_ = true;

        while (running_) {
            // 等待间隔
            timer_.expires_after(std::chrono::milliseconds(worker_config_.batch_interval_ms));
            
            try {
                co_await timer_.async_wait(asio::use_awaitable);
            } catch (const boost::system::system_error& e) {
                if (e.code() == asio::error::operation_aborted) {
                    break;
                }
                throw;
            }

            // 批量入库
            try {
                co_await flush_to_database(*conn);
            } catch (const std::exception& e) {
                std::println("[DbWorker] Batch insert error: {}", e.what());
            }
        }
    }

    // 创建数据库连接
    std::optional<pg::connection> create_connection() {
        try {
            pg::connection_config config;
            config.host = db_config_.host;
            config.port = db_config_.port;
            config.dbname = db_config_.database;
            config.user = db_config_.user;
            
            // 只有配置了密码时才设置，否则使用 pgpass
            if (db_config_.password.has_value()) {
                config.password = *db_config_.password;
            }

            std::println("[DbWorker] Connecting to PostgreSQL at {}:{} (database: {}, user: {})", 
                db_config_.host, db_config_.port, db_config_.database, db_config_.user);

            return pg::connection{config};
        } catch (const std::exception& e) {
            std::println("[DbWorker] Database connection failed: {}", e.what());
            return std::nullopt;
        }
    }

    // 从 Redis 读取并写入数据库
    asio::awaitable<void> flush_to_database(pg::connection& conn) {
        // 这里我们不清空 Redis，只是获取最近的消息进行入库
        // 实际生产中应该使用更复杂的标记机制
        // 学习项目简化处理：每次入库最新的 batch_size 条消息
        
        try {
            auto messages = co_await cache_->get_recent_messages(worker_config_.batch_size);
            
            if (messages.empty()) {
                co_return;
            }

            std::println("[DbWorker] Flushing {} messages to database", messages.size());

            // 批量插入
            for (const auto& msg : messages) {
                // 使用原生 SQL (sqlpp23 的 INSERT 语法)
                // 这里使用简化的方式
                try {
                    auto query = std::format(
                        "INSERT INTO messages (sender, content) VALUES ('{}', '{}') "
                        "ON CONFLICT DO NOTHING",
                        escape_string(msg.sender),
                        escape_string(msg.content)
                    );
                    conn.execute(query);
                } catch (const std::exception& e) {
                    std::println("[DbWorker] Insert error for message from {}: {}", 
                        msg.sender, e.what());
                }
            }

            std::println("[DbWorker] Batch insert completed");
        } catch (const std::exception& e) {
            std::println("[DbWorker] Failed to get messages from Redis: {}", e.what());
        }
    }

    // 简单的 SQL 转义 (生产环境应使用参数化查询)
    static std::string escape_string(const std::string& s) {
        std::string result;
        result.reserve(s.size() * 2);
        for (char c : s) {
            if (c == '\'') {
                result += "''";
            } else if (c == '\\') {
                result += "\\\\";
            } else {
                result += c;
            }
        }
        return result;
    }

    asio::io_context& db_ioc_;
    asio::steady_timer timer_;
    std::shared_ptr<RedisCache> cache_;
    DatabaseConfig db_config_;
    DbWorkerConfig worker_config_;
    bool running_{false};
};

}  // namespace chat
