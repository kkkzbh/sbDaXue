#pragma once

// 主服务器类
// 管理双 io_context 线程池架构

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>

#include <memory>
#include <thread>
#include <vector>
#include <print>

#include "config.hpp"
#include "session.hpp"
#include "room.hpp"
#include "redis_cache.hpp"
#include "db_worker.hpp"

namespace chat {

namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class Server {
public:
    explicit Server(Config config)
        : config_{std::move(config)}
        , chat_ioc_{static_cast<int>(config_.thread_pool.chat_pool_size)}
        , db_ioc_{static_cast<int>(config_.thread_pool.db_pool_size)}
        , acceptor_{chat_ioc_}
        , signals_{chat_ioc_, SIGINT, SIGTERM}
    {}

    // 启动服务器
    void run() {
        // 设置信号处理
        setup_signals();

        // 初始化组件
        init_components();

        // 启动 TCP acceptor
        start_accept();

        // 启动线程池
        start_thread_pools();

        std::println("[Server] Running on {}:{}", config_.server.host, config_.server.port);
        std::println("[Server] Press Ctrl+C to stop");

        // 主线程也参与 chat_ioc 工作
        chat_ioc_.run();

        // 等待所有线程结束
        for (auto& t : chat_threads_) {
            if (t.joinable()) t.join();
        }
        for (auto& t : db_threads_) {
            if (t.joinable()) t.join();
        }

        std::println("[Server] Shutdown complete");
    }

private:
    // 设置信号处理
    void setup_signals() {
        signals_.async_wait([this](auto, auto) {
            std::println("\n[Server] Received shutdown signal");
            shutdown();
        });
    }

    // 初始化组件
    void init_components() {
        // 创建 Redis 缓存
        redis_cache_ = std::make_shared<RedisCache>(chat_ioc_, config_.redis);
        redis_cache_->start();

        // 创建聊天房间
        room_ = std::make_shared<Room>(chat_ioc_, redis_cache_, config_.history.push_count);

        // 创建数据库工作者
        db_worker_ = std::make_shared<DbWorker>(
            db_ioc_, redis_cache_, config_.database, config_.db_worker);
        db_worker_->start();

        std::println("[Server] Components initialized");
    }

    // 启动 TCP acceptor
    void start_accept() {
        tcp::endpoint endpoint{
            asio::ip::make_address(config_.server.host),
            config_.server.port
        };

        acceptor_.open(endpoint.protocol());
        acceptor_.set_option(tcp::acceptor::reuse_address(true));
        acceptor_.bind(endpoint);
        acceptor_.listen();

        asio::co_spawn(chat_ioc_,
            [this] { return accept_loop(); },
            asio::detached);
    }

    // 接受连接循环
    asio::awaitable<void> accept_loop() {
        while (acceptor_.is_open()) {
            try {
                auto socket = co_await acceptor_.async_accept(asio::use_awaitable);
                
                // 创建并启动会话
                auto session = std::make_shared<Session>(std::move(socket), room_);
                session->start();
            } catch (const boost::system::system_error& e) {
                if (e.code() != asio::error::operation_aborted) {
                    std::println("[Server] Accept error: {}", e.what());
                }
            }
        }
    }

    // 启动线程池
    void start_thread_pools() {
        // Chat 线程池 (保留一个线程给主线程)
        for (std::size_t i = 1; i < config_.thread_pool.chat_pool_size; ++i) {
            chat_threads_.emplace_back([this] {
                chat_ioc_.run();
            });
        }

        // DB 线程池
        for (std::size_t i = 0; i < config_.thread_pool.db_pool_size; ++i) {
            db_threads_.emplace_back([this] {
                db_ioc_.run();
            });
        }

        std::println("[Server] Thread pools started: chat={}, db={}", 
            config_.thread_pool.chat_pool_size, config_.thread_pool.db_pool_size);
    }

    // 关闭服务器
    void shutdown() {
        std::println("[Server] Shutting down...");

        // 停止接受新连接
        acceptor_.close();

        // 停止 DB Worker
        if (db_worker_) {
            db_worker_->stop();
        }

        // 取消 Redis 连接
        if (redis_cache_) {
            redis_cache_->cancel();
        }

        // 停止 io_context
        chat_ioc_.stop();
        db_ioc_.stop();
    }

    Config config_;

    // 双 io_context 架构
    asio::io_context chat_ioc_;  // 前台聊天
    asio::io_context db_ioc_;     // 后台数据库

    tcp::acceptor acceptor_;
    asio::signal_set signals_;

    // 组件
    std::shared_ptr<RedisCache> redis_cache_;
    std::shared_ptr<Room> room_;
    std::shared_ptr<DbWorker> db_worker_;

    // 线程池
    std::vector<std::thread> chat_threads_;
    std::vector<std::thread> db_threads_;
};

}  // namespace chat
