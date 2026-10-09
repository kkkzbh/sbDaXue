#pragma once

// 配置管理模块
// 使用 toml++ 解析 TOML 配置文件

#include <toml++/toml.hpp>
#include <string>
#include <cstdint>
#include <filesystem>
#include <stdexcept>
#include <print>

namespace chat {

struct ServerConfig {
    std::string host{"0.0.0.0"};
    std::uint16_t port{8888};
};

struct ThreadPoolConfig {
    std::size_t chat_pool_size{4};
    std::size_t db_pool_size{2};
};

struct RedisConfig {
    std::string host{"127.0.0.1"};
    std::uint16_t port{6379};
    std::string message_list_key{"chat:messages"};
    std::size_t max_cached_messages{50};
};

struct DatabaseConfig {
    std::string host{"127.0.0.1"};
    std::uint16_t port{5432};  // PostgreSQL 默认端口
    std::string database{"learnrm"};
    std::string user{"kkkzbh"};
    std::optional<std::string> password;  // 为空则使用 pgpass
};

struct HistoryConfig {
    std::size_t push_count{50};
};

struct DbWorkerConfig {
    std::size_t batch_interval_ms{5000};
    std::size_t batch_size{100};
};

struct Config {
    ServerConfig server;
    ThreadPoolConfig thread_pool;
    RedisConfig redis;
    DatabaseConfig database;
    HistoryConfig history;
    DbWorkerConfig db_worker;

    // 从 TOML 文件加载配置
    static Config load(const std::filesystem::path& path) {
        if (!std::filesystem::exists(path)) {
            throw std::runtime_error(std::format("Config file not found: {}", path.string()));
        }

        auto tbl = toml::parse_file(path.string());
        Config cfg;

        // Server
        if (auto server = tbl["server"].as_table()) {
            cfg.server.host = server->get("host")->value_or(cfg.server.host);
            cfg.server.port = static_cast<std::uint16_t>(
                server->get("port")->value_or(static_cast<int64_t>(cfg.server.port)));
        }

        // Thread Pool
        if (auto tp = tbl["thread_pool"].as_table()) {
            cfg.thread_pool.chat_pool_size = static_cast<std::size_t>(
                tp->get("chat_pool_size")->value_or(static_cast<int64_t>(cfg.thread_pool.chat_pool_size)));
            cfg.thread_pool.db_pool_size = static_cast<std::size_t>(
                tp->get("db_pool_size")->value_or(static_cast<int64_t>(cfg.thread_pool.db_pool_size)));
        }

        // Redis
        if (auto redis = tbl["redis"].as_table()) {
            cfg.redis.host = redis->get("host")->value_or(cfg.redis.host);
            cfg.redis.port = static_cast<std::uint16_t>(
                redis->get("port")->value_or(static_cast<int64_t>(cfg.redis.port)));
            cfg.redis.message_list_key = redis->get("message_list_key")->value_or(cfg.redis.message_list_key);
            cfg.redis.max_cached_messages = static_cast<std::size_t>(
                redis->get("max_cached_messages")->value_or(static_cast<int64_t>(cfg.redis.max_cached_messages)));
        }

        // Database
        if (auto db = tbl["database"].as_table()) {
            cfg.database.host = db->get("host")->value_or(cfg.database.host);
            cfg.database.port = static_cast<std::uint16_t>(
                db->get("port")->value_or(static_cast<int64_t>(cfg.database.port)));
            cfg.database.database = db->get("database")->value_or(cfg.database.database);
            cfg.database.user = db->get("user")->value_or(cfg.database.user);
            if (auto pwd = db->get("password")) {
                cfg.database.password = pwd->value_or(std::string{});
            }
        }

        // History
        if (auto hist = tbl["history"].as_table()) {
            cfg.history.push_count = static_cast<std::size_t>(
                hist->get("push_count")->value_or(static_cast<int64_t>(cfg.history.push_count)));
        }

        // DB Worker
        if (auto worker = tbl["db_worker"].as_table()) {
            cfg.db_worker.batch_interval_ms = static_cast<std::size_t>(
                worker->get("batch_interval_ms")->value_or(static_cast<int64_t>(cfg.db_worker.batch_interval_ms)));
            cfg.db_worker.batch_size = static_cast<std::size_t>(
                worker->get("batch_size")->value_or(static_cast<int64_t>(cfg.db_worker.batch_size)));
        }

        std::println("[Config] Loaded from {}", path.string());
        std::println("[Config] Server: {}:{}", cfg.server.host, cfg.server.port);
        std::println("[Config] Thread pools: chat={}, db={}", 
            cfg.thread_pool.chat_pool_size, cfg.thread_pool.db_pool_size);

        return cfg;
    }
};

}  // namespace chat
