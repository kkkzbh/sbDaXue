// 简易聊天服务器入口
// 基于现代 C++26，使用 boost.asio + boost.redis + sqlpp23

#include <print>
#include <filesystem>

#include "src/config.hpp"
#include "src/server.hpp"

int main(int argc, char* argv[]) {
    std::println("===========================================");
    std::println("  Simple Chat Server - Learning Project");
    std::println("  C++26 | Boost.Asio | Boost.Redis | SQLPP23");
    std::println("===========================================\n");

    try {
        // 确定配置文件路径
        std::filesystem::path config_path = "config/server.toml";
        if (argc > 1) {
            config_path = argv[1];
        }

        // 加载配置
        std::println("[Main] Loading config from: {}", config_path.string());
        auto config = chat::Config::load(config_path);

        // 创建并运行服务器
        chat::Server server{std::move(config)};
        server.run();

    } catch (const std::exception& e) {
        std::println("[Main] Fatal error: {}", e.what());
        return 1;
    }

    return 0;
}